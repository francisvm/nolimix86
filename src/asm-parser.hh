#pragma once

#include <ast/program.hh>

#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

#include <memory>

namespace nolimix86
{

  class asm_parser
  {
    public:
      asm_parser(std::unique_ptr<llvm::MemoryBuffer>);

      ~asm_parser();

      /// Parse the source file, return true if an error occured.
      bool parse();

      /// Release the ownership of the parsed program.
      ast::program program_release();

    private:
      llvm::SourceMgr src_mgr_;

      // Pimpl: hide LLVM dependencies
      struct impl;
      std::unique_ptr<impl> impl_;
  };

} // namespace nolimix86
