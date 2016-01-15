#pragma once

#include <ast/fwd.hh>

namespace nolimix86
{

  namespace ast
  {

    template<template <typename> class Const>
    void
    visitor_impl<Const>::operator()(const_t<ast>& e)
    {
      e.accept(*this);
    }

    template<template <typename> class Const>
    void
    visitor_impl<Const>::operator()(const_t<instr_base>& e)
    {
      e.accept(*this);
    }

    template<template <typename> class Const>
    void
    visitor_impl<Const>::operator()(const_t<operand>& e)
    {
      e.accept(*this);
    }

  } // namespace ast

} // namespace nolimix86
