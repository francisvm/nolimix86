#include <streamer.hh>
#include <misc/meta.hh>
#include <x86/x86.hh>
#include <ast/all.hh>
#include <ast/apply-visitor.hh>

#include <llvm/MC/MCSymbol.h>

#include <cassert>
#include <vector>

namespace nolimix86
{
  namespace
  {

    ast::operand
    emit_operand(const llvm::MCOperand& op)
    {
      if (op.isReg() && op.getReg() >= x86::max_valid_reg)
        return ast::make_operand<ast::operand::temp_tag>(
          static_cast<uint32_t>(op.getReg()));
      else if (op.isReg())
        return ast::make_operand<ast::operand::reg_tag>(
          static_cast<enum x86::reg>(op.getReg()));
      else if (op.isImm())
        return ast::make_operand<ast::operand::imm_tag>(
          static_cast<size_t>(op.getImm()));
      else
        assert(!"Unknown operand.");
    }

    ast::operand
    emit_operand(const llvm::MCOperand& op,
                 const std::vector<ast::basic_block>& program)
    {
      if (op.isExpr() && op.getExpr()->getKind() == llvm::MCExpr::SymbolRef)
      {
        const auto operand_expr
          = static_cast<const llvm::MCSymbolRefExpr*>(op.getExpr());
        const auto& label_symbol = operand_expr->getSymbol().getName().str();
        auto bb = std::find_if(program.begin(), program.end(),
                               [&](const auto& elt)
                               {
                                 return label_symbol == elt.label_get();
                               });

        assert(bb != program.end()
               && "The label is not referring to any known symbol");

        return ast::make_operand<ast::operand::label_tag>(*bb);
      }
      else
        assert(!"Unknown operand.");
    }

    ast::operand
    emit_operand(size_t offset, enum x86::reg reg)
    {
      return ast::make_operand<ast::operand::mem_tag>(offset, reg);
    }

    // Declaration of the generic visitor dispatcher.
    struct visit_instr
    {
      template <typename Instr>
      static
      std::enable_if_t<Instr::operands == 1>
      visit(ast::apply_visitor<visit_instr>&, Instr&);

      template <typename Instr>
      static
      std::enable_if_t<Instr::operands == 2>
      visit(ast::apply_visitor<visit_instr>&, Instr&);

      template <typename Instr>
      static
      std::enable_if_t<Instr::operands != 2 && Instr::operands != 1>
      visit(ast::apply_visitor<visit_instr>&, Instr&);
    };

    // Visitor applying the generic visitor dispatcher on each node.
    struct instr_operand_emitter : public ast::apply_visitor<visit_instr>
    {
      using super_type = ast::apply_visitor<visit_instr>;
      using super_type::operator();

      const llvm::MCInst& inst_;
      const std::vector<ast::basic_block>& program_;

      instr_operand_emitter(const llvm::MCInst& inst,
                            const std::vector<ast::basic_block>& program)
        : inst_{inst}
        , program_{program}
      {}

      // Special case for lea. The destination doesn't appear twice.
      void
      operator()(ast::lea& e)
      {
        // [dst][reg][?][?][offset][?]
        size_t offset = inst_.getOperand(4).getImm();
        auto reg = static_cast<enum x86::reg>(inst_.getOperand(1).getReg());
        e.set_operand(0, emit_operand(offset, reg));
        e.set_operand(1, emit_operand(inst_.getOperand(0)));

      }

      // Special case for instr mem, reg for some instructions.
      template <typename Instr>
      void
      emit_special_mr(Instr& e)
      {
        // [dst][reg][?][?][offset][?]
        size_t offset = inst_.getOperand(4).getImm();
        auto reg = static_cast<enum x86::reg>(inst_.getOperand(1).getReg());
        e.set_operand(0, emit_operand(offset, reg));
        e.set_operand(1, emit_operand(inst_.getOperand(0)));
      }

      template <typename Instr>
      void
      emit_label_operand(Instr& e)
      {
        assert(inst_.getOperand(0).isExpr());
        assert(inst_.getOperand(0).getExpr()->getKind()
               == llvm::MCExpr::SymbolRef);

        e.set_operand(0, emit_operand(inst_.getOperand(0), program_));
      }

      // Special case for mov-mr with no size specifier.
      void
      operator()(ast::mov& e)
      {
        if (inst_.size() == 6 && inst_.getOpcode() == 1664)
          emit_special_mr(e);
        else
          super_type::operator()(e);
      }

      void
      operator()(ast::cmp& e)
      {
        if (inst_.size() == 6 && inst_.getOpcode() == 572)
          emit_special_mr(e);
        else
          super_type::operator()(e);
      }

      // Two kinds of rets:
      // `ret` and `ret $0` (they are equivalent)
      void
      operator()(ast::ret& e)
      {
        if (inst_.size())
          super_type::operator()(e);
        else
          e.set_operand(0, ast::make_operand<ast::operand::imm_tag>(0UL));
      }

      void
      operator()(ast::test& e)
      {
        // test imm %eax is [imm]
        if (inst_.size() == 1)
        {
          e.set_operand(0, emit_operand(inst_.getOperand(0)));
          e.set_operand(1, ast::make_operand<ast::operand::reg_tag>("eax"));
        }
        // test operands are commutative, and llvm canonicalizes it
        else if (inst_.size() == 6 && inst_.getOpcode() == 2936)
          emit_special_mr(e);
        else
          super_type::operator()(e);
      }

// :(
#define emit_label_for(instr)                                                  \
      void                                                                     \
      operator()(ast::instr & e)                                               \
      {                                                                        \
        emit_label_operand(e);                                                 \
      }

      emit_label_for(call)
      emit_label_for(ja)
      emit_label_for(jae)
      emit_label_for(jb)
      emit_label_for(jbe)
      emit_label_for(je)
      emit_label_for(jg)
      emit_label_for(jge)
      emit_label_for(jl)
      emit_label_for(jle)
      emit_label_for(jmp)
      emit_label_for(jne)
      emit_label_for(js)
#undef emit_label_for
    };

    // Handle unary instructions.
    template <typename Instr>
    std::enable_if_t<Instr::operands == 1>
    visit_instr::visit(ast::apply_visitor<visit_instr>& v_g, Instr& e)
    {
      auto& v = static_cast<instr_operand_emitter&>(v_g);
      if (v.inst_.size() == 1)
      {
        // [dst]
        e.set_operand(0, emit_operand(v.inst_.getOperand(0)));
      }
      else if (v.inst_.size() == 2)
      {
        // [dst][dst]
        e.set_operand(0, emit_operand(v.inst_.getOperand(0)));
      }
      else if (v.inst_.size() == 5) // Memory operand.
      {
        // [reg][?][?][offset][?]
        size_t offset = v.inst_.getOperand(3).getImm();
        auto reg = static_cast<enum x86::reg>(v.inst_.getOperand(0).getReg());
        e.set_operand(0, emit_operand(offset, reg));
      }
    }

    // Handle binary instructions.
    template <typename Instr>
    std::enable_if_t<Instr::operands == 2>
    visit_instr::visit(ast::apply_visitor<visit_instr>& v_g, Instr& e)
    {
      auto& v = static_cast<instr_operand_emitter&>(v_g);
      // Registers, temporaries and immediates.
      if (v.inst_.size() == 2)
      {
        // [dst][src]
        e.set_operand(0, emit_operand(v.inst_.getOperand(1)));
        e.set_operand(1, emit_operand(v.inst_.getOperand(0)));
      }
      else if (v.inst_.size() == 3)
      {
        // [dst][dst][src]
        e.set_operand(0, emit_operand(v.inst_.getOperand(2)));
        e.set_operand(1, emit_operand(v.inst_.getOperand(1)));
      }
      else if (v.inst_.size() == 6) // Memory as a destination.
      {
        // [reg][?][?][offset][?][src]
        e.set_operand(0, emit_operand(v.inst_.getOperand(5)));
        size_t offset = v.inst_.getOperand(3).getImm();
        auto reg = static_cast<enum x86::reg>(v.inst_.getOperand(0).getReg());
        e.set_operand(1, emit_operand(offset, reg));
      }
      else if (v.inst_.size() == 7) // Memory as a source.
      {
        // [dst][dst][reg][?][?][offset][?]
        size_t offset = v.inst_.getOperand(5).getImm();
        auto reg = static_cast<enum x86::reg>(v.inst_.getOperand(2).getReg());
        e.set_operand(0, emit_operand(offset, reg));
        e.set_operand(1, emit_operand(v.inst_.getOperand(0)));
      }
    }

    // Handle the rest.
    template <typename Instr>
    std::enable_if_t<Instr::operands != 2 && Instr::operands != 1>
    visit_instr::visit(ast::apply_visitor<visit_instr>&, Instr&)
    {
      assert(!"Not implemented yet");
    }

    void
    emit_instr_operands(ast::instr_base& instr, const llvm::MCInst& inst,
                        const std::vector<ast::basic_block>& program)
    {
      instr_operand_emitter emitter{inst, program};
      emitter(instr);
    }

  }

  streamer::streamer(llvm::MCContext& Context, llvm::MCAsmBackend& TAB,
                     llvm::raw_pwrite_stream& OS, llvm::MCCodeEmitter* Emitter)
    : llvm::MCELFStreamer(Context, TAB, OS, Emitter)
  {
    program_.emplace_back("start");
  }

  void
  streamer::EmitLabel(llvm::MCSymbol* symbol)
  {
    // section labels are not registered. FIXME: Why?
    if (!symbol->isRegistered())
      program_.emplace_back(symbol->getName().str());
  }

  void
  streamer::EmitInstruction(const llvm::MCInst& inst,
                            const llvm::MCSubtargetInfo&)
  {
    auto opcode = find_opcode<x86::x86_set>(inst.getOpcode());
    auto instr = ast::make_x86_instruction(opcode);

    if (instr->size() > 0)
      emit_instr_operands(*instr, inst, program_);

    program_.back().push_back(std::move(instr));
  }

  bool
  streamer::EmitSymbolAttribute(llvm::MCSymbol* symbol,
                                llvm::MCSymbolAttr)
  {
    llvm::outs() << symbol->getName() << ": (attribute)\n";
    return true;
  }

} // namespace nolimix86
