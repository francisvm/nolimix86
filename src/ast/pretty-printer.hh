#pragma once

#include <ast/default-visitor.hh>

#include <ostream>
#include <iostream>

namespace nolimix86
{

  namespace ast
  {

    class pretty_printer : public const_default_visitor
    {
      public:
        using super_type = const_default_visitor;
        using super_type::operator();

        pretty_printer();

        ~pretty_printer();

        void operator()(const operand&) override;

        void operator()(const add&) override;

        void operator()(const call&) override;

        void operator()(const cmp&) override;

        void operator()(const idiv&) override;

        void operator()(const imul&) override;

        void operator()(const ja&) override;

        void operator()(const jae&) override;

        void operator()(const jb&) override;

        void operator()(const jbe&) override;

        void operator()(const je&) override;

        void operator()(const jg&) override;

        void operator()(const jge&) override;

        void operator()(const jl&) override;

        void operator()(const jle&) override;

        void operator()(const jmp&) override;

        void operator()(const jne&) override;

        void operator()(const js&) override;

        void operator()(const lea&) override;

        void operator()(const leave&) override;

        void operator()(const mov&) override;

        void operator()(const neg&) override;

        void operator()(const pop&) override;

        void operator()(const push&) override;

        void operator()(const ret&) override;

        void operator()(const sal&) override;

        void operator()(const sar&) override;

        void operator()(const sete&) override;

        void operator()(const sub&) override;

        void operator()(const test&) override;

        void operator()(const basic_block&) override;

      private:
        std::ostream& ostream_ = std::cout;
    };

  } // namespace ast

} // namespace nolimix86
