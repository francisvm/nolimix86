#include <ast/operand.hh>

namespace nolimix86
{

  namespace ast
  {

    void operand::accept(const_visitor& v) const
    {
      v(*this);
    }

    void operand::accept(visitor& v)
    {
      v(*this);
    }

  } // namespace ast

} // namespace nolimix86
