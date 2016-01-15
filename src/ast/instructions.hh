#pragma once

#include <ast/instr.hh>

namespace nolimix86
{

  namespace ast
  {

    class mov : public instr<1664, 2>
    {
    };

    class push : public instr<2294, 1>
    {
    };

  } // namespace ast

} // namespace nolimix86
