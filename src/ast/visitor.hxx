#pragma once

#include <ast/fwd.hh>
#include <ast/ast.hh>

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

  } // namespace ast

} // namespace nolimix86
