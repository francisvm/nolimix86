#pragma once

#include <ast/instr-base.hh>

#include <unordered_map>
#include <vector>
#include <iterator>

namespace nolimix86
{

  namespace ast
  {

    class program
    {
    public:
      using instr_t = instr_base;
      using instr_ptr_t = std::unique_ptr<instr_t>;
      using instrs_t = std::vector<instr_ptr_t>;

      using iterator = typename instrs_t::iterator;
      using const_iterator = typename instrs_t::const_iterator;

      using label_t = std::string;
      using labels_t = std::unordered_map<label_t, iterator>;

      program() = default;
      program(program&&) = default;
      program& operator=(program&&) = default;

      iterator begin();
      const_iterator begin() const;

      iterator end();
      const_iterator end() const;

      size_t size() const;

      iterator label(const label_t&);
      const_iterator label(const label_t&) const;
      const labels_t& labels_get() const;

      void set_label(label_t, iterator);
      void push_back(instr_ptr_t);

      instr_t& operator[](size_t);
      const instr_t& operator[](size_t) const;
      instr_t& operator[](const label_t&);
      const instr_t& operator[](const label_t&) const;

    private:
      labels_t labels_;
      instrs_t program_;
    };

  } // namespace ast

} // namespace nolimix86
