#pragma once

#include <ast/default-visitor.hh>
#include <ast/all.hh>

namespace nolimix86
{

  namespace ast
  {

    template <template <typename> class Const>
    template <typename T>
    void
    default_visitor_impl<Const>::visit_instr(T& e)
    {
      for (auto& operand : e)
        operand.accept(*this);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<instr_base>&)
    {
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<operand>&)
    {
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<add>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<call>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<cmp>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<idiv>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<imul>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<ja>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<jae>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<jb>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<jbe>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<je>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<jg>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<jge>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<jl>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<jle>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<jmp>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<jne>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<js>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<lea>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<leave>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<mov>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<neg>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<pop>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<push>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<ret>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<sal>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<sar>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<sete>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<sub>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<test>& e)
    {
      visit_instr(e);
    }

    template <template <typename> class Const>
    void
    default_visitor_impl<Const>::operator()(const_t<basic_block>& e)
    {
      for (auto& instr : e)
        instr->accept(*this);
    }

  } // namespace ast

} // namespace nolimix86
