#pragma once

namespace nolimia32
{

  namespace ast
  {

    template<template <typename> class Const>
    void visitor_impl<Const>::operator()(const_t<instr>&)
    {
    }

  } // namespace ast

} // namespace nolimia32
