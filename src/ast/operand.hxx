#pragma once

#include <ast/operand.hh>

namespace nolimix86
{

  namespace ast
  {

    template <typename Tag, typename... Args>
    operand make_operand(Args&&... args)
    {
      return operand{args..., Tag{}};
    }

  } // namespace ast

} // namespace nolimix86
