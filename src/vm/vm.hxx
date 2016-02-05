#pragma once

#include <vm/vm.hh>
#include <vm/cpu.hh>
#include <x86/flags.hh>

#include <limits>
#include <algorithm>

namespace nolimix86
{

  namespace vm
  {

    template <typename Cpu>
    typename vm<Cpu>::instr_t*
    vm<Cpu>::fetch()
    {
      if (fetch_queue_.size() == 0)
        return nullptr;

      auto instr = fetch_queue_.back();
      fetch_queue_.pop_back();
      return instr;
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::add& e)
    {
      cpu_.set_value(e.dst(), cpu_.value_of(e.src()) + cpu_.value_of(e.dst()));
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::call&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::cmp& e)
    {
      cpu_.reset_flags();

      {
        auto src_big = static_cast<int64_t>(cpu_.value_of(e.src()));
        auto dst_big = static_cast<int64_t>(cpu_.value_of(e.dst()));
        auto temp = src_big - dst_big;

        // Check for overflow.
        if (temp > std::numeric_limits<decltype(temp)>::max()
            || temp < std::numeric_limits<decltype(temp)>::min())
          cpu_.set_flag(Cpu::flag_t::OF, 1);

        // Check for equality.
        if (temp == 0)
          cpu_.set_flag(Cpu::flag_t::ZF, 1);

        // Check for sign.
        if (temp <= 0)
          cpu_.set_flag(Cpu::flag_t::SF, 1);
      }

      // "Below" is the result of a signed comparaison.
      {
        auto src_big = static_cast<uint64_t>(cpu_.value_of(e.src()));
        auto dst_big = static_cast<uint64_t>(cpu_.value_of(e.dst()));
        if (src_big < dst_big)
          cpu_.set_flag(Cpu::flag_t::CF, 1);
      }

      // FIXME: Parity flag

    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::idiv&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::imul& e)
    {
      cpu_.set_value(e.dst(), cpu_.value_of(e.src()) * cpu_.value_of(e.dst()));
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
    vm<Cpu>::operator()(const ast::mov& e)
    {
      cpu_.set_value(e.dst(), cpu_.value_of(e.src()));
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::neg&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::pop& e)
    {
      cpu_.pop(e.oper());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::push& e)
    {
      cpu_.push(e.oper());
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
    vm<Cpu>::operator()(const ast::sub& e)
    {
      cpu_.set_value(e.dst(), cpu_.value_of(e.dst()) - cpu_.value_of(e.src()));
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::test&)
    {
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::basic_block& e)
    {
      // Push the instructions in the fetch_queue_.
      std::transform(e.begin(), e.end(), std::back_inserter(fetch_queue_),
                     [](auto& instr)
                     {
                       return instr.get();
                     });
    }

  } // namespace vm

} // namespace nolimix86
