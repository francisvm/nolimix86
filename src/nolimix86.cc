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
dump_state("Y", llvm::cl::desc("Dump cpu's state at the end of the program"),
           llvm::cl::init(false));

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

  auto the_program = parser.program_release();

  if (dump_ast)
  {
    nolimix86::ast::pretty_printer printer;
    printer(the_program);
    return 0;
  }

  if (eval)
  {
    nolimix86::vm::x86 vm;
    vm(the_program);
  }

  if (dump_state)
  {
    nolimix86::vm::x86 vm;
    vm(the_program);

    const auto& cpu = vm.cpu_get();
    cpu.dump_state();
  }

  return 0;
}
