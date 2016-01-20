#include <streamer.hh>

#include <misc/meta.hh>
#include <x86/x86.hh>
#include <ast/all.hh>

#include <llvm/MC/MCSymbol.h>

namespace nolimix86
{
  namespace
  {

    ast::operand emit_operand(const llvm::MCOperand& op)
    {
      if (op.isReg() && op.getReg() >= x86::max_valid_reg)
        return ast::make_operand<ast::operand::temp_tag>(
          static_cast<size_t>(op.getReg()));
      else if (op.isImm())
        return ast::make_operand<ast::operand::imm_tag>(
          static_cast<size_t>(op.getImm()));
      else
        return ast::operand{10}; // FIXME: Handle all the operands.
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
    for (size_t i = 0; i < instr->size(); ++i)
      instr->set_operand(i, emit_operand(inst.getOperand(i)));

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
