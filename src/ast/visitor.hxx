#pragma once

namespace nolimix86
{

  namespace ast
  {

    template<template <typename> class Const>
    void visitor_impl<Const>::operator()(const_t<ast>&)
    {
    }

  } // namespace ast

} // namespace nolimix86
