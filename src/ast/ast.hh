#pragma once

#include <ast/visitor.hh>

namespace nolimix86
{

  namespace ast
  {

    class ast
    {
      public:
        ast() = default;
        virtual ~ast() = default;

        virtual void accept(const_visitor&) const = 0;
        virtual void accept(visitor&) = 0;
    };

  } // namespace ast

} // namespace nolimix86
