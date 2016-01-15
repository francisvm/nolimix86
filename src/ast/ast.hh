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

        void accept(const_visitor&) const;
        void accept(visitor&);
    };

  } // namespace ast

} // namespace nolimix86
