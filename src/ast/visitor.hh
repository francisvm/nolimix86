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

        virtual void operator()(const_t<operand>&);
    };

    /// Const visitor: does not alter the AST.
    using const_visitor = visitor_impl<std::add_const>;
    /// Non-const visitor: modifies the AST.
    using visitor = visitor_impl<std::remove_const>;

  } // namespace ast

} // namespace nolimix86

#include <ast/visitor.hxx>
