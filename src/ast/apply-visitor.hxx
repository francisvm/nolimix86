#pragma once

#include <ast/apply-visitor.hh>
#include <ast/all.hh>

#define visit_instr(instr)                                                     \
  template <template <typename> class Const, typename Func>                    \
  void                                                                         \
  apply_visitor_impl<Const, Func>::operator()(const_t<instr> & e)              \
  {                                                                            \
    Func::visit(*this, e);                                                     \
  }

namespace nolimix86
{

  namespace ast
  {

    template <template <typename> class Const, typename Func>
    void
    apply_visitor_impl<Const, Func>::operator()(const_t<instr_base>& e)
    {
      super_type::operator()(e);
    }

    template <template <typename> class Const, typename Func>
    void
    apply_visitor_impl<Const, Func>::operator()(const_t<operand>&)
    {
    }

    template <template <typename> class Const, typename Func>
    void
    apply_visitor_impl<Const, Func>::operator()(const_t<basic_block>& e)
    {
      for (auto& instr : e)
        instr->accept(*this);
    }

    visit_instr(add)
    visit_instr(call)
    visit_instr(cmp)
    visit_instr(idiv)
    visit_instr(imul)
    visit_instr(ja)
    visit_instr(jae)
    visit_instr(jb)
    visit_instr(jbe)
    visit_instr(je)
    visit_instr(jg)
    visit_instr(jge)
    visit_instr(jl)
    visit_instr(jle)
    visit_instr(jmp)
    visit_instr(jne)
    visit_instr(js)
    visit_instr(lea)
    visit_instr(leave)
    visit_instr(mov)
    visit_instr(neg)
    visit_instr(pop)
    visit_instr(push)
    visit_instr(ret)
    visit_instr(sal)
    visit_instr(sar)
    visit_instr(sete)
    visit_instr(sub)
    visit_instr(test)
#undef visit_instr

  } // namespace ast

} // namespace nolimix86
