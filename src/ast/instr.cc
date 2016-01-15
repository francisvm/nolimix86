#include <ast/instr.hh>

namespace nolimix86
{

  namespace ast
  {

    void instr::accept(const_visitor& v) const
    {
      v(*this);
    }

    void instr::accept(visitor& v)
    {
      v(*this);
    }



  } // namespace ast

} // namespace nolimix86
