#pragma once

#include <ast/apply-visitor.hh>

namespace nolimix86
{

  namespace ast
  {

    struct visit_instr
    {
      template <typename Visitor, typename T>
      static
      void
      visit(Visitor& v, T& e)
      {
        for (auto& operand : e)
          operand.accept(v);
      }
    };

    template<template <typename> class Const>
    class default_visitor_impl : public apply_visitor_impl<Const, visit_instr>
    {
      public:
        template <typename T>
        using const_t = typename Const<T>::type;

        using super_type = apply_visitor_impl<Const, visit_instr>;
        using super_type::operator();
    };

    /// Const visitor: does not alter the AST.
    using const_default_visitor = default_visitor_impl<std::add_const>;
    /// Non-const visitor: modifies the AST.
    using default_visitor = default_visitor_impl<std::remove_const>;

  } // namespace ast

} // namespace nolimix86

#include <ast/default-visitor.hxx>
