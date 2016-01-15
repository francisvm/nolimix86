#pragma once

#include <llvm/MC/MCELFStreamer.h>

namespace nolimix86
{

  class streamer : public llvm::MCELFStreamer
  {
    using llvm::MCELFStreamer::MCELFStreamer;

    void EmitLabel(llvm::MCSymbol* symbol) override;
    void EmitInstruction(const llvm::MCInst& inst,
                         const llvm::MCSubtargetInfo&) override;
    bool EmitSymbolAttribute(llvm::MCSymbol* symbol,
                             llvm::MCSymbolAttr) override;
  };

} // namespace nolimix86
