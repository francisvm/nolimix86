#include <ast/ast.hh>

namespace nolimix86
{

  namespace ast
  {

    void ast::accept(const_visitor& v) const
    {
      v(*this);
    }

    void ast::accept(visitor& v)
    {
      v(*this);
    }

  } // namespace ast

} // namespace nolimix86
