#include <asm-parser.hh>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>

static llvm::cl::opt<std::string>
input_filename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
               llvm::cl::init("-"));

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

  return 0;
}
