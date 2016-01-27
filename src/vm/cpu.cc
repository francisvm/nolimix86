#include <vm/cpu.hh>

namespace nolimix86
{

  namespace cpu
  {

    typename x86::word_t
    x86::value_of(const ast::operand&)
    {
      // FIXME: Indirect call to the operand.
      return {};
    }

    void
    x86::set_value(const ast::operand&, word_t)
    {
      // FIXME: Set the value to the operand depending on the type.
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
