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
      using stream_t = llvm::raw_ostream;
      using word_t = uint32_t;
      using reg_t = ast::operand::reg_t;
      using flag_t = ::nolimix86::x86::flag;
      using memory_t = cpu::memory<word_t>;
      using mmu_t = cpu::mmu<x86>;
      using stack_t = cpu::stack<word_t>;
      using heap_t = cpu::heap<word_t>;
      static constexpr auto word_size = sizeof (word_t);
      static constexpr auto name = "x86";

      /// Create an x86 virtual machine.
      x86();

      /// Get the value of an operand.
      word_t value_of(const ast::operand&);

      /// Set the value of a register/memory.
      void set_value(const ast::operand&, word_t);

      /// Set the value of a flag.
      void set_flag(flag_t, word_t);

      /// Check if a flag is set.
      bool is_flag_set(flag_t);

      /// Get the value of a flag.
      word_t flag(flag_t);

      /// Reset all the flags to 0.
      void reset_flags();

      /// Actions on the stack.
      void push(const ast::operand&);
      void pop(const ast::operand&);

      /// Dump the current state of the CPU.
      void dump_state(stream_t& os = llvm::outs()) const;

      std::unordered_map<reg_t, word_t> regs_;
      std::unordered_map<flag_t, word_t> eflags_;
      memory_t mem_;
      stack_t stack_;
      heap_t heap_;
      mmu_t mmu_;
    };

  } // namespace vm

} // namespace nolimix86
