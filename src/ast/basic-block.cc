#include <ast/basic-block.hh>
#include <ast/instr-base.hh>

namespace nolimix86

{

  namespace ast
  {

    // instr_base is an incomplete type in the header.
    basic_block::basic_block(std::string label)
      : label_{std::move(label)}
    {
    }

    basic_block::~basic_block() = default;

    typename basic_block::instr_iterator
    basic_block::begin()
    {
      return instructions_.begin();
    }

    typename basic_block::instr_const_iterator
    basic_block::begin() const
    {
      return instructions_.cbegin();
    }

    typename basic_block::instr_iterator
    basic_block::end()
    {
      return instructions_.end();
    }

    typename basic_block::instr_const_iterator
    basic_block::end() const
    {
      return instructions_.cend();
    }

    typename basic_block::instr_reverse_iterator
    basic_block::rbegin()
    {
      return instructions_.rbegin();
    }

    typename basic_block::instr_const_reverse_iterator
    basic_block::rbegin() const
    {
      return instructions_.crbegin();
    }

    typename basic_block::instr_reverse_iterator
    basic_block::rend()
    {
      return instructions_.rend();
    }

    typename basic_block::instr_const_reverse_iterator
    basic_block::rend() const
    {
      return instructions_.crend();
    }

    size_t
    basic_block::size() const
    {
      return instructions_.size();
    }

    typename basic_block::instr_t&
    basic_block::operator[](size_t i)
    {
      return *instructions_[i];
    }

    const typename basic_block::instr_t&
    basic_block::operator[](size_t i) const
    {
      return *instructions_[i];
    }

    void
    basic_block::push_back(typename basic_block::instr_ptr_t instr)
    {
      instructions_.push_back(std::move(instr));
    }

    const std::string&
    basic_block::label_get() const
    {
      return label_;
    }

    void
    basic_block::accept(const_visitor& v) const
    {
      v(*this);
    }

    void
    basic_block::accept(visitor& v)
    {
      v(*this);
    }

    bool
    operator==(const basic_block& lhs, const basic_block& rhs)
    {
      return lhs.label_get() == rhs.label_get();
    }

  } // namespace ast

} // namespace nolimix86
