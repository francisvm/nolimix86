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
    const typename vm<Cpu>::cpu_t&
    vm<Cpu>::cpu_get() const
    {
      return cpu_;
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
    vm<Cpu>::operator()(const ast::ja& e)
    {
      if (!cpu_.is_flag_set(Cpu::flag_t::CF)
          && !cpu_.is_flag_set(Cpu::flag_t::ZF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jae& e)
    {
      if (!cpu_.is_flag_set(Cpu::flag_t::CF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jb& e)
    {
      if (cpu_.is_flag_set(Cpu::flag_t::CF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jbe& e)
    {
      if (cpu_.is_flag_set(Cpu::flag_t::CF)
          || cpu_.is_flag_set(Cpu::flag_t::ZF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::je& e)
    {
      if (cpu_.is_flag_set(Cpu::flag_t::ZF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jg& e)
    {
      if (!cpu_.is_flag_set(Cpu::flag_t::ZF)
          && cpu_.flag(Cpu::flag_t::SF) == cpu_.flag(Cpu::flag_t::OF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jge& e)
    {
      if (cpu_.flag(Cpu::flag_t::SF) == cpu_.flag(Cpu::flag_t::OF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jl& e)
    {
      if (cpu_.flag(Cpu::flag_t::SF) != cpu_.flag(Cpu::flag_t::OF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jle& e)
    {
      if (cpu_.is_flag_set(Cpu::flag_t::ZF)
          && cpu_.flag(Cpu::flag_t::SF) != cpu_.flag(Cpu::flag_t::OF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jmp& e)
    {
      jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::jne& e)
    {
      if (!cpu_.is_flag_set(Cpu::flag_t::ZF))
        jump_to(e.oper().label_get());
    }

    template <typename Cpu>
    void
    vm<Cpu>::operator()(const ast::js& e)
    {
      if (cpu_.is_flag_set(Cpu::flag_t::SF))
        jump_to(e.oper().label_get());
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
      {
        auto ebp = ast::make_operand<ast::operand::reg_tag>("ebp");
        auto pop = ast::pop{std::move(ebp)};
        (*this)(pop);
      }
      {
        auto ebp = ast::make_operand<ast::operand::reg_tag>("ebp");
        auto esp = ast::make_operand<ast::operand::reg_tag>("esp");
        auto mov = ast::mov{std::move(ebp), std::move(esp)};
        (*this)(mov);
      }
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
    vm<Cpu>::operator()(const ast::program& e)
    {
      eip_ = e.begin();
      while (eip_ != e.end())
      {
        (*this)(**eip_);
        ++eip_;
      }
    }

    template <typename Cpu>
    void
    vm<Cpu>::jump_to(const ast::operand::label_t& e)
    {
      // Jump to the previous instruction, since eip is going to advance.
      eip_ = std::prev(e.second);
    }

  } // namespace vm

} // namespace nolimix86
