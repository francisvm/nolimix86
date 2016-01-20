#include <ast/instr-base.hh>

namespace nolimix86
{

  namespace ast
  {

    void
    instr_base::accept(const_visitor& v) const
    {
      v(*this);
    }

    void
    instr_base::accept(visitor& v)
    {
      v(*this);
    }

  } // namespace ast

} // namespace nolimix86
