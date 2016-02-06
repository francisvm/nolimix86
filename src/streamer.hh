#pragma once

#include <ast/fwd.hh>
#include <ast/basic-block.hh>

#include <llvm/MC/MCELFStreamer.h>

#include <vector>

namespace nolimix86
{

  struct label_streamer : public llvm::MCELFStreamer
  {
    public:
      using llvm::MCELFStreamer::MCELFStreamer;

      label_streamer(llvm::MCContext&, llvm::MCAsmBackend&,
                     llvm::raw_pwrite_stream&, llvm::MCCodeEmitter*);

      void EmitLabel(llvm::MCSymbol* symbol) override;
      void EmitInstruction(const llvm::MCInst& inst,
                           const llvm::MCSubtargetInfo&) override;
      bool EmitSymbolAttribute(llvm::MCSymbol* symbol,
                               llvm::MCSymbolAttr) override;

      /// The resulting ast.
      std::vector<ast::basic_block> program_;
  };

  struct streamer : public llvm::MCELFStreamer
  {
    public:
      using llvm::MCELFStreamer::MCELFStreamer;

      streamer(std::vector<ast::basic_block>&, llvm::MCContext&,
               llvm::MCAsmBackend&, llvm::raw_pwrite_stream&,
               llvm::MCCodeEmitter*);

      void EmitLabel(llvm::MCSymbol* symbol) override;
      void EmitInstruction(const llvm::MCInst& inst,
                           const llvm::MCSubtargetInfo&) override;
      bool EmitSymbolAttribute(llvm::MCSymbol* symbol,
                               llvm::MCSymbolAttr) override;

      /// The resulting ast.
      std::vector<ast::basic_block>& program_;

    private:
      /// The current block where the instructions are being attached.
      ast::basic_block* current_block_ = nullptr;
  };

} // namespace nolimix86
