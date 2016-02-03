#include <vm/cpu.hh>

namespace nolimix86
{

  namespace cpu
  {

    namespace
    {
      constexpr auto default_size = 4096;
    }

    x86::x86()
      : mem_{std::make_unique<word_t[]>(default_size)}
      , stack_{mem_.get()}
      , mmu_{reinterpret_cast<typename mmu_t::host_address_t>(mem_.get())}
    {
      // Set the stack pointer
      regs_[reg_t::ESP] = mmu_.host_to_vm(mmu_.base_);
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
        assert(!"Not implemented yet.");
        //const auto offset = op.mem_offset_get();
        //const auto reg = op.mem_reg_get();
      }
      else if (op.is_label())
      {
        assert(!"Not implemented yet.");
        //const auto& bb = op.label_bb_get();
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
        assert(!"Not implemented yet.");
        //const auto offset = op.mem_offset_get();
        //const auto reg = op.mem_reg_get();
      }
      else
      {
        assert(!"Not implemented yet.");
      }
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
    x86::dump_state() const
    {
      llvm::outs() << "=============================\n"
                      "Stack:\t\tindex\tvalue\n";

      for (auto it = stack_.begin(); it != stack_.end(); ++it)
      {
        const auto& elt = *it;
        auto i = std::distance(stack_.begin(), it);
        llvm::outs() << "\t\t" << i << "\t" << elt << '\n';
      }

      llvm::outs() << "-----------------------------\n"
                      "Registers:\tid\tvalue\n";

      for (const auto& reg_pair: regs_)
        llvm::outs() << "\t\t" << reg_pair.first
                   << "\t" << reg_pair.second << '\n';
    }

  } // namespace cpu

} // namespace nolimix86
