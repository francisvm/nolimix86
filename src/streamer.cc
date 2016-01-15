#include <llvm/MC/MCSymbol.h>

#include <streamer.hh>

namespace nolimia32
{

  void
  streamer::EmitLabel(llvm::MCSymbol* symbol)
  {
    llvm::outs() << symbol->getName() << ":\n";
    // FIXME : Implement AST.
  }

  void
  streamer::EmitInstruction(const llvm::MCInst& inst,
                            const llvm::MCSubtargetInfo&)
  {
    llvm::outs() << inst << '\n';
    // FIXME : Implement AST.
  }

  bool
  streamer::EmitSymbolAttribute(llvm::MCSymbol* symbol,
                                llvm::MCSymbolAttr)
  {
    llvm::outs() << symbol->getName() << ": (attribute)\n";
    return true;
  };

} // namespace nolimia32
