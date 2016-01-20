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

        virtual ~pretty_printer();

        virtual void operator()(const operand&) override;

        virtual void operator()(const add&) override;

        virtual void operator()(const call&) override;

        virtual void operator()(const cmp&) override;

        virtual void operator()(const idiv&) override;

        virtual void operator()(const imul&) override;

        virtual void operator()(const ja&) override;

        virtual void operator()(const jae&) override;

        virtual void operator()(const jb&) override;

        virtual void operator()(const jbe&) override;

        virtual void operator()(const je&) override;

        virtual void operator()(const jg&) override;

        virtual void operator()(const jge&) override;

        virtual void operator()(const jl&) override;

        virtual void operator()(const jle&) override;

        virtual void operator()(const jmp&) override;

        virtual void operator()(const jne&) override;

        virtual void operator()(const js&) override;

        virtual void operator()(const lea&) override;

        virtual void operator()(const leave&) override;

        virtual void operator()(const mov&) override;

        virtual void operator()(const neg&) override;

        virtual void operator()(const pop&) override;

        virtual void operator()(const push&) override;

        virtual void operator()(const ret&) override;

        virtual void operator()(const sal&) override;

        virtual void operator()(const sar&) override;

        virtual void operator()(const sete&) override;

        virtual void operator()(const sub&) override;

        virtual void operator()(const test&) override;

        virtual void operator()(const basic_block&) override;

      private:
        std::ostream& ostream_ = std::cout;
    };

  } // namespace ast

} // namespace nolimix86
