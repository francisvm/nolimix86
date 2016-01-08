#include <program.hh>

namespace nolimia32
{

  program::program(std::unique_ptr<llvm::MemoryBuffer> buffer)
  {
    src_mgr_.AddNewSourceBuffer(std::move(buffer), {});
  }

} // namespace nolimia32
