#pragma once

#include <llvm/Support/raw_ostream.h>

#include <string>
#include <cstdint>
#include <cstdlib>

namespace nolimix86
{

  using std::size_t;

  using opcode_t = uint16_t;

  [[noreturn]]
  inline
  void
  die(const std::string& msg)
  {
    llvm::errs() << msg << '\n';
    std::abort();
  }

} // namespace nolimix86
