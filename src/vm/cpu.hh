#pragma once

#include <ast/operand.hh>
#include <x86/registers.hh>
#include <vm/mmu.hh>
#include <vm/memory.hh>

#include <vector>
#include <unordered_map>
#include <memory>

namespace nolimix86
{

  namespace cpu
  {

    struct x86
    {
      using word_t = uint32_t;
      using reg_t = ast::operand::reg_t;
      using memory_t = cpu::memory<word_t>;
      using mmu_t = cpu::mmu<x86>;
      using stack_t = cpu::stack<word_t>;
      using heap_t = cpu::heap<word_t>;
      static constexpr auto word_size = sizeof (word_t);

      /// Create an x86 virtual machine.
      x86();

      /// Get the value of an operand.
      word_t value_of(const ast::operand&);

      /// Set the value of a register/memory.
      void set_value(const ast::operand&, word_t);

      /// Actions on the stack.
      void push(const ast::operand&);
      void pop(const ast::operand&);

      /// Dump the current state of the CPU.
      void dump_state() const;

      std::unordered_map<reg_t, word_t> regs_;
      memory_t mem_;
      stack_t stack_;
      heap_t heap_;
      mmu_t mmu_;
    };

  } // namespace vm

} // namespace nolimix86
