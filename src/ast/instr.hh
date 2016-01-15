#pragma once

#include <ast/visitor.hh>

namespace nolimix86
{

  namespace ast
  {

    class instr
    {
      public:
        instr() = default;
        virtual ~instr() = default;

        void accept(const_visitor&) const;
        void accept(visitor&);
    };

  } // namespace ast

} // namespace nolimix86
