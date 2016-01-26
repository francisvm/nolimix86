#pragma once

#include <vm/vm.hh>
#include <vm/cpu.hh>

namespace nolimix86
{

  namespace vm
  {

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::add&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::call&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::cmp&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::idiv&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::imul&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::ja&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jae&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jb&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jbe&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::je&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jg&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jge&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jl&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jle&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jmp&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jne&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::js&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::lea&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::leave&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::mov&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::neg&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::pop&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::push&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::ret&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::sal&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::sar&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::sete&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::sub&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::test&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::basic_block&)
    {
    }

  } // namespace vm

} // namespace nolimix86
