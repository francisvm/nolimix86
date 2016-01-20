#include <ast/default-visitor.hh>
#include <ast/all.hh>

#include <gtest/gtest.h>

#include <algorithm>

namespace ast = nolimix86::ast;

TEST(ast_node, basic_block)
{
  ast::basic_block bb;
  EXPECT_EQ(bb.size(), 0);
  EXPECT_EQ(std::distance(bb.begin(), bb.end()), 0);
}

TEST(ast_node, basic_block_filled)
{
  ast::basic_block bb;
  bb.push_back(
    std::make_unique<ast::add>(ast::operand(10), ast::operand("eax")));
  bb.push_back(std::make_unique<ast::jmp>(
    ast::make_operand<ast::operand::label_tag>("l0")));
  EXPECT_EQ(bb.size(), 2);
  EXPECT_EQ(std::distance(bb.begin(), bb.end()), 2);
}

TEST(ast_node, visit_basic_block)
{
  struct bb_visitor : public ast::const_default_visitor
  {
    using super_type = ast::const_default_visitor;
    using super_type::operator();

    int i = 0;
    void operator()(const ast::basic_block&) override
    {
      ++i;
    }
  };

  ast::basic_block bb;
  bb_visitor visitor;
  EXPECT_EQ(visitor.i, 0);
  visitor(bb);
  EXPECT_EQ(visitor.i, 1);
}

TEST(ast_node, default_visit_basic_block)
{
  struct bb_visitor : public ast::const_default_visitor
  {
    using super_type = ast::const_default_visitor;
    using super_type::operator();

    int i = 0;
    void operator()(const ast::mov&) override
    {
      ++i;
    }
  };

  ast::basic_block bb;
  bb.push_back(std::make_unique<ast::mov>(ast::operand(10), ast::operand(11)));
  bb_visitor visitor;
  EXPECT_EQ(visitor.i, 0);
  visitor(bb);
  EXPECT_EQ(visitor.i, 1);
}

TEST(default_visitor, const_default_visitor)
{
  ast::const_default_visitor visitor;
}

TEST(default_visitor, default_visitor)
{
  ast::default_visitor visitor;
}

TEST(default_visitor, visit_instructions)
{
  struct op_visitor : public ast::const_default_visitor
  {
    using super_type = ast::const_default_visitor;
    using super_type::operator();

    int i = 0;
    void operator()(const ast::operand&) override
    {
      ++i;
    }
  };

  ast::basic_block bb;
  bb.push_back(std::make_unique<ast::mov>(ast::operand(10), ast::operand(11)));
  bb.push_back(std::make_unique<ast::mov>(ast::operand("eax"), ast::operand("ebx")));
  op_visitor visitor;
  EXPECT_EQ(visitor.i, 0);
  visitor(bb);
  EXPECT_EQ(visitor.i, 4);
}

TEST(instr, construction)
{
  ast::instr<10, 1> unary{ast::operand(10)};
  ast::instr<16, 2> binary{ast::operand(10), ast::operand("eax")};
  ast::instr<24, 0> nop;
  EXPECT_EQ(unary.opcode_get(), 10);
  EXPECT_EQ(binary.opcode_get(), 16);
  EXPECT_EQ(nop.opcode_get(), 24);
  unary.operand();
  binary.src();
  binary.dst();
}
