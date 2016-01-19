#include <ast/default-visitor.hh>

#include <gtest/gtest.h>

namespace ast = nolimix86::ast;

TEST(default_visitor, const_default_visitor)
{
  ast::const_default_visitor visitor;
}

TEST(default_visitor, default_visitor)
{
  ast::default_visitor visitor;
}
