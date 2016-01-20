#pragma once

#include <ast/fwd.hh>
#include <ast/basic-block.hh>

#include <llvm/MC/MCELFStreamer.h>

#include <vector>

namespace nolimix86
{

  class streamer : public llvm::MCELFStreamer
  {
    public:
      using llvm::MCELFStreamer::MCELFStreamer;

      void EmitLabel(llvm::MCSymbol* symbol) override;
      void EmitInstruction(const llvm::MCInst& inst,
                           const llvm::MCSubtargetInfo&) override;
      bool EmitSymbolAttribute(llvm::MCSymbol* symbol,
                               llvm::MCSymbolAttr) override;

    private:
      /// The resulting ast.
      std::vector<ast::basic_block> program_;
  };

} // namespace nolimix86
