#pragma once

#include <ast/visitor.hh>

namespace nolimix86
{

  namespace ast
  {

    template<template <typename> class Const>
    class default_visitor_impl : public visitor_impl<Const>
    {
      public:
        template <typename T>
        using const_t = typename Const<T>::type;

        virtual void operator()(const_t<instr_base>&) override;

        virtual void operator()(const_t<operand>&) override;

        virtual void operator()(const_t<add>&) override;

        virtual void operator()(const_t<call>&) override;

        virtual void operator()(const_t<cmp>&) override;

        virtual void operator()(const_t<idiv>&) override;

        virtual void operator()(const_t<imul>&) override;

        virtual void operator()(const_t<ja>&) override;

        virtual void operator()(const_t<jae>&) override;

        virtual void operator()(const_t<jb>&) override;

        virtual void operator()(const_t<jbe>&) override;

        virtual void operator()(const_t<je>&) override;

        virtual void operator()(const_t<jg>&) override;

        virtual void operator()(const_t<jge>&) override;

        virtual void operator()(const_t<jl>&) override;

        virtual void operator()(const_t<jle>&) override;

        virtual void operator()(const_t<jmp>&) override;

        virtual void operator()(const_t<jne>&) override;

        virtual void operator()(const_t<js>&) override;

        virtual void operator()(const_t<lea>&) override;

        virtual void operator()(const_t<leave>&) override;

        virtual void operator()(const_t<mov>&) override;

        virtual void operator()(const_t<neg>&) override;

        virtual void operator()(const_t<pop>&) override;

        virtual void operator()(const_t<push>&) override;

        virtual void operator()(const_t<ret>&) override;

        virtual void operator()(const_t<sal>&) override;

        virtual void operator()(const_t<sar>&) override;

        virtual void operator()(const_t<sete>&) override;

        virtual void operator()(const_t<sub>&) override;

        virtual void operator()(const_t<test>&) override;

        virtual void operator()(const_t<basic_block>&) override;

      private:
        template <typename T>
        void visit_instr(T&);
    };

    /// Const visitor: does not alter the AST.
    using const_default_visitor = default_visitor_impl<std::add_const>;
    /// Non-const visitor: modifies the AST.
    using default_visitor = default_visitor_impl<std::remove_const>;

  } // namespace ast

} // namespace nolimix86

#include <ast/default-visitor.hxx>
