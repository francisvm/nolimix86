#include <vm/cpu.hh>

namespace nolimix86
{

  namespace cpu
  {

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
      stack_.push_back(value_of(op));
      regs_[reg_t::ESP] += word_size;
    }

    void
    x86::pop(const ast::operand& op)
    {
      set_value(op, stack_.back());
      stack_.pop_back();
      regs_[reg_t::ESP] -= word_size;
    }

  } // namespace cpu

} // namespace nolimix86
