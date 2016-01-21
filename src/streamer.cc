#include <streamer.hh>
#include <misc/meta.hh>
#include <x86/x86.hh>
#include <ast/all.hh>
#include <ast/default-visitor.hh>

#include <llvm/MC/MCSymbol.h>

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
        return ast::operand{10}; // FIXME: Handle all the operands.
    }

    struct instr_operand_emitter : public ast::default_visitor
    {
      using super_type = ast::default_visitor;
      using super_type::operator();

      const llvm::MCInst& inst_;

      instr_operand_emitter(const llvm::MCInst& inst)
        : inst_{inst}
      {}

      void
      operator()(ast::add& e) override
      {
        e.set_operand(0, emit_operand(inst_.getOperand(2)));
        e.set_operand(1, emit_operand(inst_.getOperand(1)));
      }

    };

    void
    emit_instr_operands(ast::instr_base& instr, const llvm::MCInst& inst)
    {
      instr_operand_emitter emitter{inst};
      emitter(instr);
    }

  }

  void
  streamer::EmitLabel(llvm::MCSymbol* symbol)
  {
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
  };

} // namespace nolimix86
