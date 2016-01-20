#pragma once

#include <ast/ast.hh>
#include <ast/visitor.hh>

namespace nolimix86
{

  namespace ast
  {

    class instr_base : public ast
    {
      public:
        void accept(const_visitor&) const override;
        void accept(visitor&) override;

        virtual opcode_t opcode_get() const noexcept = 0;

        virtual size_t size() const = 0;

        virtual void set_operand(size_t, operand) = 0;
    };

  } // namespace ast

} // namespace nolimix86
