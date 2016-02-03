#include <vm/allocator.hh>

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace vm = nolimix86::vm;

TEST(vm_allocator, construction)
{
  vm::vm_stack_allocator<int> alloc;
  vm::vm_stack_allocator<int> alloc1{10};
  vm::vm_stack_allocator<std::string> alloc2;
}

TEST(vm_allocator, allocate)
{
  std::vector<int, vm::vm_stack_allocator<int>> v;
  v.push_back(10);
  v.push_back(10);
  v.push_back(10);
  v.push_back(10);
}

TEST(vm_allocator, deallocate)
{
  std::vector<int, vm::vm_stack_allocator<int>> v;
  v.push_back(10);
  v.push_back(10);
  v.push_back(10);
  v.push_back(10);

  v.pop_back();
  v.pop_back();
  v.pop_back();
  v.pop_back();
}

TEST(vm_allocator, allocate_ptr)
{
  std::vector<int, vm::vm_stack_allocator<int>> v;
  v.push_back(10);
  v.push_back(10);
  v.push_back(10);
  v.push_back(10);

  ASSERT_LT(&v[0], &v[1]);
  ASSERT_LT(&v[1], &v[2]);
  ASSERT_LT(&v[2], &v[3]);
}
