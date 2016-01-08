#pragma once
#include <llvm/Support/SourceMgr.h>

namespace nolimia32
{

class program
{
  public:
    program() = default;
    program(std::unique_ptr<llvm::MemoryBuffer>);

  private:
    llvm::SourceMgr src_mgr_;
};

} // namespace nolimia32
