#include <asm-parser.hh>

#include <ast/default-visitor.hh>
#include <ast/pretty-printer.hh>
#include <vm/vm.hh>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>

#include <string>

static llvm::cl::opt<std::string>
input_filename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
               llvm::cl::init("-"));

static llvm::cl::opt<bool>
dump_ast("A", llvm::cl::desc("Dump the ast on stdout"), llvm::cl::init(false));

static llvm::cl::opt<bool>
eval("e", llvm::cl::desc("Evaluate the parsed ast"), llvm::cl::init(false));

int main(int argc, char const *argv[])
{
  llvm::cl::ParseCommandLineOptions(argc, argv, "nolimix86\n");

  auto buffer_ptr = llvm::MemoryBuffer::getFileOrSTDIN(input_filename);
  if (auto ec = buffer_ptr.getError())
  {
    llvm::errs() << input_filename << ": " << ec.message() << '\n';
    return 1;
  }

  nolimix86::asm_parser parser{std::move(*buffer_ptr)};

  if (parser.parse())
    return 1;

  auto blocks = parser.program_release();

  if (dump_ast)
  {
    nolimix86::ast::pretty_printer printer;
    for (const auto& block : blocks)
      printer(block);
    return 0;
  }

  if (eval)
  {
    nolimix86::vm::x86 vm{blocks};

    // Add all the basic blocks to the fetch queue.
    for (auto& block : blocks)
      vm(block);

    while (auto instr = vm.fetch())
    {
      vm(*instr);
    }

    return 0;
  }

  return 0;
}
