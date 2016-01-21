#pragma once

#include <ast/visitor.hh>

namespace nolimix86
{

  namespace ast
  {

    struct no_op
    {
      template <typename Visitor, typename T>
      static
      void
      visit(const Visitor&, const T&)
      {
      }
    };

    template<template <typename> class Const, typename Func = no_op>
    class apply_visitor_impl : public visitor_impl<Const>
    {
      public:
        template <typename T>
        using const_t = typename Const<T>::type;

        using super_type = visitor_impl<Const>;

        void operator()(const_t<instr_base>&) override;

        void operator()(const_t<operand>&) override;

        void operator()(const_t<add>&) override;

        void operator()(const_t<call>&) override;

        void operator()(const_t<cmp>&) override;

        void operator()(const_t<idiv>&) override;

        void operator()(const_t<imul>&) override;

        void operator()(const_t<ja>&) override;

        void operator()(const_t<jae>&) override;

        void operator()(const_t<jb>&) override;

        void operator()(const_t<jbe>&) override;

        void operator()(const_t<je>&) override;

        void operator()(const_t<jg>&) override;

        void operator()(const_t<jge>&) override;

        void operator()(const_t<jl>&) override;

        void operator()(const_t<jle>&) override;

        void operator()(const_t<jmp>&) override;

        void operator()(const_t<jne>&) override;

        void operator()(const_t<js>&) override;

        void operator()(const_t<lea>&) override;

        void operator()(const_t<leave>&) override;

        void operator()(const_t<mov>&) override;

        void operator()(const_t<neg>&) override;

        void operator()(const_t<pop>&) override;

        void operator()(const_t<push>&) override;

        void operator()(const_t<ret>&) override;

        void operator()(const_t<sal>&) override;

        void operator()(const_t<sar>&) override;

        void operator()(const_t<sete>&) override;

        void operator()(const_t<sub>&) override;

        void operator()(const_t<test>&) override;

        void operator()(const_t<basic_block>&) override;
    };

    /// Const visitor: does not alter the AST.
    template <typename Func>
    using const_apply_visitor = apply_visitor_impl<std::add_const, Func>;
    /// Non-const visitor: modifies the AST.
    template <typename Func>
    using apply_visitor = apply_visitor_impl<std::remove_const, Func>;

  } // namespace ast

} // namespace nolimix86

#include <ast/apply-visitor.hxx>
