#include <vm/cpu.hh>
#include <vm/mmu.hh>

#include <gtest/gtest.h>

#include <memory>

namespace cpu = nolimix86::cpu;

TEST(mmu, construction)
{
  auto mem = std::make_unique<int[]>(1);
  cpu::mmu<cpu::x86> mmu{
      reinterpret_cast<typename cpu::mmu<cpu::x86>::host_address_t>(mem.get())};
}

TEST(mmu, host_to_vm)
{
  auto mem = std::make_unique<int[]>(2);
  auto base =
      reinterpret_cast<typename cpu::mmu<cpu::x86>::host_address_t>(mem.get());
  auto second = reinterpret_cast<typename cpu::mmu<cpu::x86>::host_address_t>(
      mem.get() + 1);

  cpu::mmu<cpu::x86> mmu{base};
  ASSERT_EQ(mmu.host_to_vm(base), 0);
  ASSERT_EQ(mmu.host_to_vm(second), 4);
}

TEST(mmu, vm_to_host)
{
  auto mem = std::make_unique<int[]>(2);
  auto base =
      reinterpret_cast<typename cpu::mmu<cpu::x86>::host_address_t>(mem.get());
  auto second = reinterpret_cast<typename cpu::mmu<cpu::x86>::host_address_t>(
      mem.get() + 1);

  cpu::mmu<cpu::x86> mmu{base};
  ASSERT_EQ(mmu.vm_to_host(0), base);
  ASSERT_EQ(mmu.vm_to_host(4), second);
}
