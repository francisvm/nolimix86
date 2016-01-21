#pragma once

#include <ast/fwd.hh>

#include <type_traits>

namespace nolimix86
{

  namespace ast
  {

    /// Visitors can be mutable or immutable visitors.
    /// Use it as visitor_impl<trait>, with trait deciding the constness
    /// of the nodes.
    template<template <typename> class Const>
    class visitor_impl
    {
      public:
        template <typename T>
        using const_t = typename Const<T>::type;

        visitor_impl() = default;
        virtual ~visitor_impl() = default;

        /// Visit an ast node
        virtual void operator()(const_t<ast>&);

        virtual void operator()(const_t<instr_base>&);

        virtual void operator()(const_t<operand>&) = 0;

        virtual void operator()(const_t<add>&) = 0;

        virtual void operator()(const_t<call>&) = 0;

        virtual void operator()(const_t<cmp>&) = 0;

        virtual void operator()(const_t<idiv>&) = 0;

        virtual void operator()(const_t<imul>&) = 0;

        virtual void operator()(const_t<ja>&) = 0;

        virtual void operator()(const_t<jae>&) = 0;

        virtual void operator()(const_t<jb>&) = 0;

        virtual void operator()(const_t<jbe>&) = 0;

        virtual void operator()(const_t<je>&) = 0;

        virtual void operator()(const_t<jg>&) = 0;

        virtual void operator()(const_t<jge>&) = 0;

        virtual void operator()(const_t<jl>&) = 0;

        virtual void operator()(const_t<jle>&) = 0;

        virtual void operator()(const_t<jmp>&) = 0;

        virtual void operator()(const_t<jne>&) = 0;

        virtual void operator()(const_t<js>&) = 0;

        virtual void operator()(const_t<lea>&) = 0;

        virtual void operator()(const_t<leave>&) = 0;

        virtual void operator()(const_t<mov>&) = 0;

        virtual void operator()(const_t<neg>&) = 0;

        virtual void operator()(const_t<pop>&) = 0;

        virtual void operator()(const_t<push>&) = 0;

        virtual void operator()(const_t<ret>&) = 0;

        virtual void operator()(const_t<sal>&) = 0;

        virtual void operator()(const_t<sar>&) = 0;

        virtual void operator()(const_t<sete>&) = 0;

        virtual void operator()(const_t<sub>&) = 0;

        virtual void operator()(const_t<test>&) = 0;

        virtual void operator()(const_t<basic_block>&) = 0;
    };

    /// Const visitor: does not alter the AST.
    using const_visitor = visitor_impl<std::add_const>;
    /// Non-const visitor: modifies the AST.
    using visitor = visitor_impl<std::remove_const>;

  } // namespace ast

} // namespace nolimix86

#include <ast/visitor.hxx>
