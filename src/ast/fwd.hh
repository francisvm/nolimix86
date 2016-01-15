#pragma once

#include <common.hh>

namespace nolimix86
{

  namespace ast
  {

    class ast;

    class instr_base;

    template <opcode_t opcode, size_t operands_count>
    class instr;

    class operand;

  } // namespace ast

} // namespace nolimix86
