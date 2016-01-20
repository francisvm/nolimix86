#pragma once

#include <ast/instructions.hh>

namespace nolimix86
{

  namespace ast
  {

    /// Find opcode inside the type list and create an instance of that type.
    template <typename... Instrs>
    struct find_instruction_impl;

    /// If it can't be found, try the next Instr.
    /// If it is found, allocate an instance of the exact class.
    template <typename Instr, typename... Instrs>
    struct find_instruction_impl<Instr, Instrs...>
    {
      template <typename... Args>
      auto operator()(size_t i, Args&&... args)
      {
        return i == Instr::opcode
                 ? std::make_unique<Instr>(args...)
                 : find_instruction_impl<Instrs...>{}(i);
      }
    };

    /// Stop and return 0 if it's not to be found.
    template <>
    struct find_instruction_impl<>
    {
      template <typename... Args>
      std::unique_ptr<instr_base> operator()(size_t, Args&&...)
      {
        return {};
      }
    };

    /// Unpack the Instrs parameters.
    template <typename Instr>
    struct find_instruction;

    template <template<typename...> class Instr, typename... Instrs>
    struct find_instruction<Instr<Instrs...>>
    {
      template <typename... Args>
      auto operator()(size_t i, Args&&... args)
      {
        return find_instruction_impl<Instrs...>{}(i,
                                                  std::forward<Args>(args)...);
      }
    };

    /// Type list of all possible Instrs.
    using x86_set = ranges<add, call, cmp, idiv, imul, ja, jae, jb, jbe, je, jg,
                           jge, jl, jle, jmp, jne, js, lea, leave, mov, neg,
                           pop, push, ret, sal, sar, sete, sub, test>;

    /// Create an instruction according to the opcode and the arguments.
    template <typename... Args>
    std::unique_ptr<instr_base>
    make_x86_instruction(opcode_t opcode, Args&&... args)
    {
      return find_instruction<x86_set>{}(opcode, std::forward<Args>(args)...);
    }

  } // namespace ast

} // namespace nolimix86
