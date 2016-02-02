#pragma once

#include <cstdlib>

namespace nolimix86
{

  namespace cpu
  {

    template <typename Cpu>
    mmu<Cpu>::mmu(typename mmu<Cpu>::host_address_t base)
      : base_{base}
    {
    }

    template <typename Cpu>
    typename mmu<Cpu>::vm_address_t
    mmu<Cpu>::host_to_vm(typename mmu<Cpu>::host_address_t host)
    {
      return std::abs(host - base_);
    }

    template <typename Cpu>
    typename mmu<Cpu>::host_address_t
    mmu<Cpu>::vm_to_host(typename mmu<Cpu>::vm_address_t vm)
    {
      return vm + base_;
    }

  } // namespace cpu

} // namespace nolimix86
