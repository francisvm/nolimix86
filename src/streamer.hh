#pragma once

#include <ast/fwd.hh>
#include <ast/basic-block.hh>

#include <llvm/MC/MCELFStreamer.h>

#include <vector>

namespace nolimix86
{

  struct streamer : public llvm::MCELFStreamer
  {
    public:
      using llvm::MCELFStreamer::MCELFStreamer;

      streamer(llvm::MCContext &Context, llvm::MCAsmBackend &TAB,
               llvm::raw_pwrite_stream &OS, llvm::MCCodeEmitter *Emitter);

      void EmitLabel(llvm::MCSymbol* symbol) override;
      void EmitInstruction(const llvm::MCInst& inst,
                           const llvm::MCSubtargetInfo&) override;
      bool EmitSymbolAttribute(llvm::MCSymbol* symbol,
                               llvm::MCSymbolAttr) override;

      /// The resulting ast.
      std::vector<ast::basic_block> program_;
  };

} // namespace nolimix86
