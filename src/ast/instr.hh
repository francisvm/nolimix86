#pragma once

#include <common.hh>
#include <ast/instr-base.hh>
#include <ast/operand.hh>
#include <ast/visitor.hh>

#include <array>

namespace nolimix86
{

  namespace ast
  {

    template <opcode_t opcode_in, size_t operands_count>
    class instr : public instr_base
    {
      public:
        using self_t = instr;
        using operand_t = operand;
        using operands_t = std::array<operand_t, operands_count>;
        using operand_iterator = typename operands_t::iterator;
        using operand_const_iterator = typename operands_t::const_iterator;

        instr() = default;

        /// Allow construction with two operands if it's a binary instruction.
        template <size_t count = operands_count,
                  typename = std::enable_if_t<count == 2>>
        instr(operand_t, operand_t);

        /// Allow construction with one operand if it's a unary instruction.
        template <size_t count = operands_count,
                  typename = std::enable_if_t<count == 1>>
        instr(operand_t);

        /// Instruction opcode
        opcode_t opcode_get() const noexcept override;

        /// Operand iterators
        operand_iterator begin() noexcept;
        operand_const_iterator begin() const noexcept;
        operand_iterator end() noexcept;
        operand_const_iterator end() const noexcept;

        /// Access an operand
        constexpr operand_t& operator[](size_t) noexcept;
        constexpr const operand_t& operator[](size_t) const noexcept;

        /// Src and dst should be available only for instructions with 2
        /// operands.
        template <size_t count = operands_count>
        constexpr std::enable_if_t<count == 2, operand_t&>
        src() noexcept;

        template <size_t count = operands_count>
        constexpr std::enable_if_t<count == 2, const operand_t&>
        src() const noexcept;

        template <size_t count = operands_count>
        constexpr std::enable_if_t<count == 2, operand_t&>
        dst() noexcept;

        template <size_t count = operands_count>
        constexpr std::enable_if_t<count == 2, const operand_t&>
        dst() const noexcept;

        /// Operand should be available only for instructions with 1 operand.
        template <size_t count = operands_count>
        constexpr std::enable_if_t<count == 1, operand_t&>
        operand() noexcept;

        template <size_t count = operands_count>
        constexpr std::enable_if_t<count == 1, const operand_t&>
        operand() const noexcept;

        void accept(const_visitor&) const override;
        void accept(visitor&) override;

        size_t size() const override;

        void set_operand(size_t, operand_t) override;

        static constexpr auto opcode = opcode_in;

      protected:
        operands_t operands_;
    };

  } // namespace ast

} // namespace nolimix86

#include <ast/instr.hxx>
