#pragma once

#include <ast/fwd.hh>
#include <ast/ast.hh>

#include <vector>
#include <memory>

namespace nolimix86
{

  namespace ast
  {

    class basic_block : public ast
    {
      public:
        using instr_t = instr_base;
        using instr_ptr_t = std::unique_ptr<instr_t>;
        using instrs_t = std::vector<instr_ptr_t>;
        using instr_iterator = typename instrs_t::iterator;
        using instr_const_iterator = typename instrs_t::const_iterator;

        /// Defaults for forward declaration of instr_base.
        basic_block();
        ~basic_block();

        /// Iterators
        instr_iterator begin();
        instr_const_iterator begin() const;
        instr_iterator end();
        instr_const_iterator end() const;

        /// Access an instruction
        instr_t& operator[](size_t);
        const instr_t& operator[](size_t) const;

        void push_back(instr_ptr_t);

      public:
        void accept(const_visitor&) const override;
        void accept(visitor&) override;

      private:
        instrs_t instructions_;
    };

  } // namespace ast

} // namespace nolimix86