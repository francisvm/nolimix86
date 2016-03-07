#include <parser/asm-parser.hh>
#include <parser/streamer.hh>
#include <ast/program.hh>
#include <ast/operand.hh>

#include <llvm/ADT/Triple.h>
#include <llvm/MC/MCAsmBackend.h>
#include <llvm/MC/MCAsmInfo.h>
#include <llvm/MC/MCCodeEmitter.h>
#include <llvm/MC/MCContext.h>
#include <llvm/MC/MCInstrInfo.h>
#include <llvm/MC/MCParser/MCAsmParser.h>
#include <llvm/MC/MCRegisterInfo.h>
#include <llvm/MC/MCObjectFileInfo.h>
#include <llvm/MC/MCTargetOptionsCommandFlags.h>
#include <llvm/MC/MCTargetAsmParser.h>
#include <llvm/Support/FileSystem.h> // llvm::sys::fs::F_None
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/ToolOutputFile.h>

#include <string>
#include <stdexcept>

namespace nolimix86
{

  namespace
  {

    void
    binder(const nolimix86::streamer::labels_t& labels,
         nolimix86::ast::program& program, std::vector<ast::operand*>& relocs)
    {
      for (const auto& label : labels)
        program.set_label(label.second,
                          std::next(program.begin(), label.first));
      for (auto reloc : relocs)
      {
        assert(reloc->is_label());
        auto new_it = program.label(reloc->label_bb_get().first);
        assert(new_it != program.end());
        reloc->update_label_it(new_it);
      }
    }

    struct llvm_parser
    {
      llvm_parser(llvm::SourceMgr& src_mgr)
        : out{"tmp" , ec, llvm::sys::fs::F_None}
        , options{InitMCTargetOptionsFromFlags()}
      {
        assert(!ec && "Unable to create tool_output_file!");

        LLVMInitializeX86TargetInfo();
        LLVMInitializeX86TargetMC();
        LLVMInitializeX86AsmParser();

        triple = [&]
        {
          const auto default_trg = llvm::sys::getDefaultTargetTriple();
          llvm::Triple triple{llvm::Triple::normalize(default_trg)};
          return triple.get32BitArchVariant();
        }();
        const auto& triple_name = triple.getTriple();

        target = [&]
        {
          std::string error;
          const auto* target
            = llvm::TargetRegistry::lookupTarget(triple_name, error);
          assert(target && "Unable to create target!");
          return target;
        }();

        reg_info.reset(target->createMCRegInfo(triple_name));
        assert(reg_info && "Unable to create target register info!");

        asm_info.reset(target->createMCAsmInfo(*reg_info, triple_name));
        assert(asm_info && "Unable to create target asm info!");

        ctx = std::make_unique<llvm::MCContext>(asm_info.get(), reg_info.get(),
                                                &ofile_info, &src_mgr);
        ofile_info.InitMCObjectFileInfo(triple, llvm::Reloc::Default,
                                        llvm::CodeModel::Default, *ctx);

        instr_info.reset(target->createMCInstrInfo());
        assert(instr_info && "Unable to create target instr info!");

        // Setup the program streamer

        backend = target->createMCAsmBackend(*reg_info, triple_name, "");
        assert(backend && "Undable to create asm backend!");

        emitter = target->createMCCodeEmitter(*instr_info, *reg_info,
                                                  *ctx);
        assert(emitter && "Undable to create code emitter!");
        // MCStreamer
        streamer = std::make_unique<nolimix86::streamer>(*ctx, *backend,
                                                         out.os(), emitter);

        // MCParser
        parser.reset(llvm::createMCAsmParser(src_mgr, *ctx, *streamer,
                                             *asm_info));

        subtarget_info.reset(target->createMCSubtargetInfo(triple_name,
                                                           "", ""));
        assert(subtarget_info && "Unable to create subtarget info!");

        target_parser.reset(target->createMCAsmParser(*subtarget_info, *parser,
                                                       *instr_info, options));
        assert(target_parser && "Unable to create target parser!");
        parser->setTargetParser(*target_parser);
      }

      bool
      operator()()
      {
        if (parser->Run(true))
          return true;
        binder(streamer->labels_, streamer->program_, streamer->relocs_);
        return false;
      }

      std::error_code ec;
      llvm::tool_output_file out;
      llvm::Triple triple;
      const llvm::Target* target;
      std::unique_ptr<const llvm::MCRegisterInfo> reg_info;
      std::unique_ptr<const llvm::MCAsmInfo> asm_info;
      llvm::MCObjectFileInfo ofile_info;
      std::unique_ptr<llvm::MCContext> ctx;
      std::unique_ptr<const llvm::MCInstrInfo> instr_info;

      // Streamer
      llvm::MCAsmBackend* backend; // Not owned.
      llvm::MCCodeEmitter* emitter; // Not owned.
      std::unique_ptr<nolimix86::streamer> streamer;
      std::unique_ptr<llvm::MCAsmParser> parser;
      std::unique_ptr<const llvm::MCSubtargetInfo> subtarget_info;
      llvm::MCTargetOptions options;
      std::unique_ptr<llvm::MCTargetAsmParser> target_parser;
    };

  }

  struct asm_parser::impl
  {
    impl(llvm::SourceMgr& src_mgr)
      : parser{src_mgr}
    {
    }

    llvm_parser parser;
  };

  asm_parser::asm_parser(std::unique_ptr<llvm::MemoryBuffer> buffer)
  {
    src_mgr_.AddNewSourceBuffer(std::move(buffer), {});

    // Delay initialization until the source manager is filled.
    impl_ = std::make_unique<impl>(src_mgr_);
  }

  bool
  asm_parser::parse()
  {
    return impl_->parser();
  }

  ast::program
  asm_parser::program_release()
  {
    return std::move(impl_->parser.streamer->program_);
  }

  asm_parser::~asm_parser() = default;

} // namespace nolimix86
