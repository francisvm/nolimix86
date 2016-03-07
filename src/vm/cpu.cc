#include <vm/cpu.hh>
#include <x86/yaml.hh>

namespace nolimix86
{

  namespace cpu
  {

    namespace
    {
      constexpr auto default_size = 4096;
    }

    x86::x86()
      : mem_{default_size}
      , stack_{mem_}
      , heap_{mem_}
      , mmu_{reinterpret_cast<typename mmu_t::host_address_t>(mem_.base())}
    {
      // Reset all the registers.
      regs_[reg_t::EAX] = 0;
      regs_[reg_t::EBX] = 0;
      regs_[reg_t::ECX] = 0;
      regs_[reg_t::EDI] = 0;
      regs_[reg_t::ESI] = 0;
      regs_[reg_t::EBP] = 0;

      // Set the stack pointer to the base of the stack.
      regs_[reg_t::ESP] = mmu_.host_to_vm(mmu_.base_);

      // Reset all the flags.
      eflags_[flag_t::CF] = 0;
      eflags_[flag_t::OF] = 0;
      eflags_[flag_t::SF] = 0;
      eflags_[flag_t::ZF] = 0;
      eflags_[flag_t::AF] = 0;
      eflags_[flag_t::PF] = 0;

      // Set the globals.
      globals_["stdin"] = 1;
      globals_["stdout"] = 2;
      globals_["stderr"] = 3;
    }

    typename x86::word_t
    x86::value_of(const ast::operand& op)
    {
      if (op.is_temp())
      {
        const auto temp = op.temp_reg_get();
        return regs_[temp];
      }
      else if (op.is_reg())
      {
        const auto reg = op.reg_get();
        return regs_[reg];
      }
      else if (op.is_imm())
      {
        const auto imm = op.imm_get();
        return imm;
      }
      else if (op.is_mem())
      {
        const auto offset = op.mem_offset_get();
        const auto reg = op.mem_reg_get();
        const auto reg_value = regs_[reg];
        const auto vm_addr = reg_value + offset;
        const auto host_addr =
            reinterpret_cast<word_t*>(mmu_.vm_to_host(vm_addr));
        return *host_addr;
      }
      else if (op.is_label())
      {
        assert(!"Not implemented yet.");
      }
      else if (op.is_symbol())
      {
        return globals_[op.symbol_get()];
      }
      else
      {
        assert(!"Not implemented yet.");
      }
    }

    void
    x86::set_value(const ast::operand& op, word_t value)
    {
      assert(!op.is_imm() && "Can't set the value of an immediate.");
      assert(!op.is_label() && "Can't set the value of a label.");
      assert(!op.is_symbol() && "Can't set the value of a label.");

      if (op.is_temp())
      {
        const auto temp = op.temp_reg_get();
        regs_[temp] = value;
      }
      else if (op.is_reg())
      {
        const auto reg = op.reg_get();
        regs_[reg] = value;
      }
      else if (op.is_mem())
      {
        const auto offset = op.mem_offset_get();
        const auto reg = op.mem_reg_get();
        const auto reg_value = regs_[reg];
        const auto vm_addr = reg_value + offset;
        const auto host_addr =
            reinterpret_cast<word_t *>(mmu_.vm_to_host(vm_addr));
        *host_addr = value;
      }
      else
      {
        assert(!"Not implemented yet.");
      }
    }

    void
    x86::set_flag(flag_t flag, word_t value)
    {
      eflags_[flag] = value;
    }

    bool
    x86::is_flag_set(flag_t flag)
    {
      return eflags_[flag] != 0;
    }

    x86::word_t
    x86::flag(flag_t fl)
    {
      return eflags_[fl];
    }

    void
    x86::reset_flags()
    {
      for (auto& pair : eflags_)
        pair.second = 0;
    }

    void
    x86::push(const ast::operand& op)
    {
      stack_.push(value_of(op));
      regs_[reg_t::ESP] += word_size;
    }

    void
    x86::pop(const ast::operand& op)
    {
      set_value(op, stack_.back());
      stack_.pop();
      regs_[reg_t::ESP] -= word_size;
    }

    void
    x86::dump_state(stream_t& os) const
    {
      llvm::yaml::Output yout{os};

      // Needed for the llvm::yaml interface. Won't actually modify anything.
      yout << const_cast<x86&>(*this);
    }

  } // namespace cpu

} // namespace nolimix86
