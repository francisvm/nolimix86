#pragma once

#include <ast/fwd.hh>
#include <ast/program.hh>

#include <llvm/MC/MCELFStreamer.h>

namespace nolimix86
{

  struct streamer : public llvm::MCELFStreamer
  {
    public:
      using labels_t = std::unordered_map<size_t, std::string>;
      using llvm::MCELFStreamer::MCELFStreamer;

      streamer(llvm::MCContext&, llvm::MCAsmBackend&,
               llvm::raw_pwrite_stream&, llvm::MCCodeEmitter*);

      void EmitLabel(llvm::MCSymbol* symbol) override;
      void EmitInstruction(const llvm::MCInst& inst,
                           const llvm::MCSubtargetInfo&) override;
      bool EmitSymbolAttribute(llvm::MCSymbol* symbol,
                               llvm::MCSymbolAttr) override;

      /// The resulting ast.
      labels_t labels_;
      ast::program program_;
      size_t ic_ = 0; // Instruction counter
      std::vector<ast::operand*> relocs_;
  };

} // namespace nolimix86
