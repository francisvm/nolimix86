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
