#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

static llvm::cl::opt<std::string>
input_filename(llvm::cl::Positional, llvm::cl::desc("<input file>"),
               llvm::cl::init("-"));

int main(int argc, char const *argv[])
{
  llvm::cl::ParseCommandLineOptions(argc, argv, "nolimia32\n");

  auto buffer_ptr = llvm::MemoryBuffer::getFileOrSTDIN(input_filename);
  if (auto ec = buffer_ptr.getError())
  {
    llvm::errs() << input_filename << ": " << ec.message() << '\n';
    return 1;
  }

  llvm::outs() << "Processing file: " << input_filename << '\n';

  return 0;
}
