#include <ast/instructions.hh>
#include <vm/vm.hh>
#include <vm/memory.hh>

#include <gtest/gtest.h>

#include <string>
#include <memory>

namespace cpu = nolimix86::cpu;
namespace vm = nolimix86::vm;
namespace ast = nolimix86::ast;

TEST(vm_x86, construction)
{
  vm::x86 vm;
}

TEST(vm_x86, visit)
{
  vm::x86 vm;
  ast::mov mov{ast::make_operand<ast::operand::temp_tag>(1U),
               ast::make_operand<ast::operand::temp_tag>(1U)};
  vm(mov);
}

TEST(vm_x86_stack, construction)
{
  {
    auto mem = cpu::memory<int>(1);
    cpu::stack<int> s{mem};
    ASSERT_EQ(s.size(), 0);
  }
  {
    auto mem = cpu::memory<std::string>(1);
    cpu::stack<std::string> s2{mem};
    ASSERT_EQ(s2.size(), 0);
  }
}

TEST(vm_x86_stack, push)
{
  auto mem = cpu::memory<int>(1);
  cpu::stack<int> s{mem};
  s.push(10);

  ASSERT_EQ(s.size(), 1);
}

TEST(vm_x86_stack, pop)
{
  auto mem = cpu::memory<int>(1);
  cpu::stack<int> s{mem};
  s.push(10);
  s.pop();

  ASSERT_EQ(s.size(), 0);
}

TEST(vm_x86_stack, loop)
{
  auto mem = cpu::memory<int>(4);
  cpu::stack<int> s{mem};
  s.push(10);
  s.push(11);
  s.push(12);
  s.push(13);

  auto i = 13;
  for (const auto& elt : s)
  {
    ASSERT_EQ(elt, i);
    --i;
  }
}

TEST(vm_x86_heap, construction)
{
  {
    auto mem = cpu::memory<int>(1);
    cpu::heap<int> s{mem};
    ASSERT_EQ(s.size(), 0);
  }
  {
    auto mem = cpu::memory<std::string>(1);
    cpu::heap<std::string> s2{mem};
    ASSERT_EQ(s2.size(), 0);
  }
}

TEST(vm_x86_heap, alloc)
{
  auto mem = cpu::memory<int>(1);
  cpu::heap<int> s{mem};
  s.alloc(10);

  ASSERT_EQ(s.size(), 1);
}

TEST(vm_x86_heap, loop)
{
  auto mem = cpu::memory<int>(4);
  cpu::heap<int> s{mem};
  s.alloc(10);
  s.alloc(11);
  s.alloc(12);
  s.alloc(13);

  auto i = 10;
  for (const auto& elt : s)
  {
    ASSERT_EQ(elt, i);
    ++i;
  }
}
