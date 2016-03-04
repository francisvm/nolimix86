#include <ast/program.hh>

namespace nolimix86
{

  namespace ast
  {

    program::iterator
    program::begin()
    {
      return program_.begin();
    }

    program::const_iterator
    program::begin() const
    {
      return program_.cbegin();
    }

    program::iterator
    program::end()
    {
      return program_.end();
    }

    program::const_iterator
    program::end() const
    {
      return program_.cend();
    }

    size_t
    program::size() const
    {
      return program_.size();
    }

    program::iterator
    program::label(const program::label_t& label)
    {
      return labels_[label];
    }

    program::const_iterator
    program::label(const program::label_t& label) const
    {
      auto it = labels_.find(label);
      return it == labels_.end() ? program_.end() : it->second;
    }

    const program::labels_t&
    program::labels_get() const
    {
      return labels_;
    }

    void
    program::set_label(program::label_t label, program::iterator it)
    {
      labels_[std::move(label)] = it;
    }

    void
    program::push_back(program::instr_ptr_t instr)
    {
      program_.push_back(std::move(instr));
    }

    program::instr_t&
    program::operator[](size_t index)
    {
      return *program_[index];
    }

    const program::instr_t&
    program::operator[](size_t index) const
    {
      return *program_[index];
    }

    program::instr_t&
    program::operator[](const program::label_t& label)
    {
      return **labels_[label];
    }

    const program::instr_t&
    program::operator[](const program::label_t& label) const
    {
      return **labels_.at(label);
    }

  } // namespace ast

} // namespace nolimix86
