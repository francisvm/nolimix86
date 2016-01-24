#include <streamer.hh>
#include <misc/meta.hh>
#include <x86/x86.hh>
#include <ast/all.hh>
#include <ast/apply-visitor.hh>

#include <llvm/MC/MCSymbol.h>

#include <cassert>

namespace nolimix86
{
  namespace
  {

    ast::operand
    emit_operand(const llvm::MCOperand& op)
    {
      if (op.isReg() && op.getReg() >= x86::max_valid_reg)
        return ast::make_operand<ast::operand::temp_tag>(
          static_cast<size_t>(op.getReg()));
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
    emit_operand(size_t offset, enum x86::reg reg)
    {
      return ast::make_operand<ast::operand::mem_tag>(offset, reg);
    }

    // Declaration of the generic visitor dispatcher.
    struct visit_instr
    {
      template <typename Instr>
      static
      std::enable_if_t<Instr::operands == 2>
      visit(ast::apply_visitor<visit_instr>&, Instr&);

      template <typename Instr>
      static
      std::enable_if_t<Instr::operands != 2>
      visit(ast::apply_visitor<visit_instr>&, Instr&);
    };

    // Visitor applying the generic visitor dispatcher on each node.
    struct instr_operand_emitter : public ast::apply_visitor<visit_instr>
    {
      using super_type = ast::apply_visitor<visit_instr>;
      using super_type::operator();

      const llvm::MCInst& inst_;

      instr_operand_emitter(const llvm::MCInst& inst)
        : inst_{inst}
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

      // Special case for mov-mr with no size specifier.
      void
      operator()(ast::mov& e)
      {
        if (inst_.size() == 6 && inst_.getOpcode() == 1663)
        {
          // [dst][reg][?][?][offset][?]
          size_t offset = inst_.getOperand(4).getImm();
          auto reg = static_cast<enum x86::reg>(inst_.getOperand(1).getReg());
          e.set_operand(0, emit_operand(offset, reg));
          e.set_operand(1, emit_operand(inst_.getOperand(0)));
        }
        else
          super_type::operator()(e);

      }

    };

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
    std::enable_if_t<Instr::operands != 2>
    visit_instr::visit(ast::apply_visitor<visit_instr>&, Instr&)
    {
      assert(!"Not implemented yet");
    }

    void
    emit_instr_operands(ast::instr_base& instr, const llvm::MCInst& inst)
    {
      instr_operand_emitter emitter{inst};
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
    if (symbol->isInSection(false))
      program_.emplace_back(symbol->getName().str());
  }

  void
  streamer::EmitInstruction(const llvm::MCInst& inst,
                            const llvm::MCSubtargetInfo&)
  {
    auto opcode = find_opcode<x86::x86_set>(inst.getOpcode());
    auto instr = ast::make_x86_instruction(opcode);

    emit_instr_operands(*instr, inst);

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
