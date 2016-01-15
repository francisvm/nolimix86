#pragma once

#include <ast/ast.hh>
#include <ast/visitor.hh>

namespace nolimix86
{

  namespace ast
  {

    class operand : public ast
    {
      public:
        void accept(const_visitor&) const override;
        void accept(visitor&) override;
    };

  } // namespace ast

} // namespace nolimix86
