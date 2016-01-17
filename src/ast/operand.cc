#include <ast/operand.hh>

namespace nolimix86
{

  namespace ast
  {

    operand::operand(size_t temp_num, operand::temp_tag)
      : impl_{std::make_unique<temp_impl>(temp_num)}
    {
    }

    operand::operand(const std::string& reg_name)
      : impl_{std::make_unique<reg_impl>(reg_name)}
    {
    }

    operand::operand(size_t imm_val)
      : impl_{std::make_unique<imm_impl>(imm_val)}
    {
    }

    operand::operand(size_t offset, const std::string& reg_name)
      : impl_{std::make_unique<mem_impl>(offset, reg_name)}
    {
    }

    void operand::accept(const_visitor& v) const
    {
      v(*this);
    }

    void operand::accept(visitor& v)
    {
      v(*this);
    }

    operand::temp_impl::temp_impl(size_t temp_num)
      : temp_num_{temp_num}
    {
    }

    operand::reg_impl::reg_impl(const std::string& reg_name)
      : reg_{x86::reg_convert(reg_name)}
    {
    }

    operand::imm_impl::imm_impl(size_t imm_val)
      : value_{imm_val}
    {
    }

    operand::mem_impl::mem_impl(size_t offset, const std::string& reg_name)
      : offset_{offset}
      , reg_{x86::reg_convert(reg_name)}
    {
    }

  } // namespace ast

} // namespace nolimix86
