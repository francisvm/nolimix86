#include <ast/operand.hh>

namespace nolimix86
{

  namespace ast
  {

    operand::operand(size_t temp_num, temp_tag)
      : impl_{std::make_unique<temp_impl>(temp_num)}
      , type_{type::TEMP}
    {
    }

    operand::operand(const std::string& reg_name, reg_tag)
      : impl_{std::make_unique<reg_impl>(reg_name)}
      , type_{type::REG}
    {
    }

    operand::operand(size_t imm_val, imm_tag)
      : impl_{std::make_unique<imm_impl>(imm_val)}
      , type_{type::IMM}
    {
    }

    operand::operand(size_t offset, const std::string& reg_name, mem_tag)
      : impl_{std::make_unique<mem_impl>(offset, reg_name)}
      , type_{type::MEM}
    {
    }

    operand::operand(std::string label_name, label_tag)
      : impl_{std::make_unique<label_impl>(std::move(label_name))}
      , type_{type::LABEL}
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

    operand::label_impl::label_impl(std::string label_name)
      : label_{std::move(label_name)}
    {
    }

    typename operand::type
    operand::type_get() const
    {
      return type_;
    }

    bool
    operand::is_temp() const
    {
      return type_ == type::TEMP;
    }

    bool
    operand::is_reg() const
    {
      return type_ == type::REG;
    }

    bool
    operand::is_imm() const
    {
      return type_ == type::IMM;
    }

    bool
    operand::is_mem() const
    {
      return type_ == type::MEM;
    }

    bool
    operand::is_label() const
    {
      return type_ == type::LABEL;
    }

  } // namespace ast

} // namespace nolimix86
