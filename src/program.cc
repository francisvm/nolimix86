#include <program.hh>
#include <llvm/MC/MCTargetOptionsCommandFlags.h>
#include <llvm/MC/MCObjectFileInfo.h>
#include <llvm/MC/MCContext.h>
#include <llvm/MC/MCParser/MCAsmParser.h>
#include <llvm/ADT/Triple.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>

namespace nolimia32
{

  program::program(std::unique_ptr<llvm::MemoryBuffer> buffer)
    : src_mgr_{}
  {
    LLVMInitializeX86TargetInfo();
    LLVMInitializeX86TargetMC();
    LLVMInitializeX86AsmParser();

    src_mgr_.AddNewSourceBuffer(std::move(buffer), {});

    auto options = InitMCTargetOptionsFromFlags();
    llvm::Triple triple{llvm::Triple::normalize(llvm::sys::getDefaultTargetTriple())};
    triple = triple.get32BitArchVariant();

    auto* target = [&]
    {
      std::string error;
      auto* target = llvm::TargetRegistry::lookupTarget(triple.getTriple(), error);
      llvm::errs() << error << '\n';
      assert(target);
      return target;
    }();

    auto triple_name = triple.getTriple();

    auto reg_info = target->createMCRegInfo(triple_name);
    assert(reg_info && "Unable to create target register info!");

    auto asm_info = target->createMCAsmInfo(*reg_info, triple_name);
    assert(asm_info && "Unable to create target asm info!");

    llvm::MCObjectFileInfo ofile_info;
    llvm::MCContext ctx{asm_info, reg_info, &ofile_info, &src_mgr_};
    ofile_info.InitMCObjectFileInfo(triple, llvm::Reloc::Default,
                                    llvm::CodeModel::Default, ctx);

    auto instr_info = target->createMCInstrInfo();
    auto subtarget_info = target->createMCSubtargetInfo(triple_name, "", "");
    auto streamer = target->createNullStreamer(ctx);

    auto parser = llvm::createMCAsmParser(src_mgr_, ctx, *streamer, *asm_info);
    auto target_parser = target->createMCAsmParser(*subtarget_info, *parser,
                                                   *instr_info, options);
    assert(target_parser);
    parser->setTargetParser(*target_parser);

    parser->Run(true);
  }

} // namespace nolimia32
