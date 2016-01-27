#pragma once

#include <ast/instr.hh>

namespace nolimix86
{

  namespace ast
  {

    template <opcode_t opcode, size_t operands_count>
    template <size_t count, typename>
    instr<opcode, operands_count>::instr(operand_t src, operand_t dst)
      : operands_{{std::move(src), std::move(dst)}}
    {
    }

    template <opcode_t opcode, size_t operands_count>
    template <size_t count, typename>
    instr<opcode, operands_count>::instr(operand_t oper)
      : operands_{{std::move(oper)}}
    {
    }

    template <opcode_t opcode, size_t operands_count>
    void
    instr<opcode, operands_count>::accept(const_visitor& v) const
    {
      v(*this);
    }

    template <opcode_t opcode, size_t operands_count>
    void
    instr<opcode, operands_count>::accept(visitor& v)
    {
      v(*this);
    }

    template <opcode_t opcode, size_t operands_count>
    size_t
    instr<opcode, operands_count>::size() const
    {
      return operands_count;
    }

    template <opcode_t opcode, size_t operands_count>
    void
    instr<opcode, operands_count>::set_operand(size_t i, operand_t operand)
    {
      operands_[i] = std::move(operand);
    }

    template <opcode_t opcode, size_t operands_count>
    opcode_t
    instr<opcode, operands_count>::opcode_get() const noexcept
    {
      return opcode;
    }

    template <opcode_t opcode, size_t operands_count>
    typename instr<opcode, operands_count>::operand_iterator
    instr<opcode, operands_count>::begin() noexcept
    {
      return operands_.begin();
    }

    template <opcode_t opcode, size_t operands_count>
    typename instr<opcode, operands_count>::operand_const_iterator
    instr<opcode, operands_count>::begin() const noexcept
    {
      return operands_.cbegin();
    }

    template <opcode_t opcode, size_t operands_count>
    typename instr<opcode, operands_count>::operand_iterator
    instr<opcode, operands_count>::end() noexcept
    {
      return operands_.end();
    }

    template <opcode_t opcode, size_t operands_count>
    typename instr<opcode, operands_count>::operand_const_iterator
    instr<opcode, operands_count>::end() const noexcept
    {
      return operands_.cend();
    }

    template <opcode_t opcode, size_t operands_count>
    constexpr
    typename instr<opcode, operands_count>::operand_t&
    instr<opcode, operands_count>::operator[](size_t i) noexcept
    {
      return operands_[i];
    }

    template <opcode_t opcode, size_t operands_count>
    constexpr
    const typename instr<opcode, operands_count>::operand_t&
    instr<opcode, operands_count>::operator[](size_t i) const noexcept
    {
      return operands_[i];
    }

    template <opcode_t opcode, size_t operands_count>
    template <size_t count>
    constexpr
    std::enable_if_t<count == 2,
                     typename instr<opcode, operands_count>::operand_t&>
    instr<opcode, operands_count>::src() noexcept
    {
      return (*this)[0];
    }

    template <opcode_t opcode, size_t operands_count>
    template <size_t count>
    constexpr
    std::enable_if_t<count == 2,
                     const typename instr<opcode, operands_count>::operand_t&>
    instr<opcode, operands_count>::src() const noexcept
    {
      return (*this)[0];
    }

    template <opcode_t opcode, size_t operands_count>
    template <size_t count>
    constexpr
    std::enable_if_t<count == 2,
                     typename instr<opcode, operands_count>::operand_t&>
    instr<opcode, operands_count>::dst() noexcept
    {
      return (*this)[1];
    }

    template <opcode_t opcode, size_t operands_count>
    template <size_t count>
    constexpr
    std::enable_if_t<count == 2,
                     const typename instr<opcode, operands_count>::operand_t&>
    instr<opcode, operands_count>::dst() const noexcept
    {
      return (*this)[1];
    }

    template <opcode_t opcode, size_t operands_count>
    template <size_t count>
    constexpr
    std::enable_if_t<count == 1,
                     typename instr<opcode, operands_count>::operand_t&>
    instr<opcode, operands_count>::oper() noexcept
    {
      return (*this)[0];
    }

    template <opcode_t opcode, size_t operands_count>
    template <size_t count>
    constexpr
    std::enable_if_t<count == 1,
                     const typename instr<opcode, operands_count>::operand_t&>
    instr<opcode, operands_count>::oper() const noexcept
    {
      return (*this)[0];
    }

  } // namespace ast

} // namespace nolimix86
