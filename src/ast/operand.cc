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

    operand::operand(enum x86::reg reg, reg_tag)
      : impl_{std::make_unique<reg_impl>(reg)}
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

    void
    operand::accept(const_visitor& v) const
    {
      v(*this);
    }

    void
    operand::accept(visitor& v)
    {
      v(*this);
    }

    operand::temp_impl::temp_impl(size_t temp_num)
      : temp_num_{temp_num}
    {
    }

    void
    operand::temp_impl::dump(llvm::raw_ostream& ostream) const
    {
      ostream << "%t" << temp_num_ - x86::max_valid_reg;
    }

    operand::reg_impl::reg_impl(const std::string& reg_name)
      : reg_{x86::reg_convert(reg_name)}
    {
    }

    operand::reg_impl::reg_impl(enum x86::reg reg)
      : reg_{reg}
    {
    }

    void
    operand::reg_impl::dump(llvm::raw_ostream& ostream) const
    {
      ostream << '%' << x86::reg_convert(reg_);
    }

    operand::imm_impl::imm_impl(size_t imm_val)
      : value_{imm_val}
    {
    }

    void
    operand::imm_impl::dump(llvm::raw_ostream& ostream) const
    {
      ostream << '$' << value_;
    }

    operand::mem_impl::mem_impl(size_t offset, const std::string& reg_name)
      : offset_{offset}
      , reg_{x86::reg_convert(reg_name)}
    {
    }

    void
    operand::mem_impl::dump(llvm::raw_ostream& ostream) const
    {
      ostream.write_hex(offset_) << '(' << x86::reg_convert(reg_) << ')';
    }

    operand::label_impl::label_impl(std::string label_name)
      : label_{std::move(label_name)}
    {
    }

    void
    operand::label_impl::dump(llvm::raw_ostream& ostream) const
    {
      ostream << label_;
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

    void
    operand::dump(llvm::raw_ostream& ostream) const
    {
      impl_->dump(ostream);
    }

  } // namespace ast

} // namespace nolimix86
