#include <ast/operand.hh>

#include <gtest/gtest.h>

TEST(Operand, Temp)
{
  nolimix86::ast::operand op{0, nolimix86::ast::operand::temp_tag{}};
}
