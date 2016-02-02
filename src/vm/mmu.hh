#pragma once

#include <cstdint>

namespace nolimix86
{

  namespace cpu
  {

    template <typename Cpu>
    struct mmu
    {
      using host_address_t = intptr_t;
      using vm_address_t = typename Cpu::word_t;
      static constexpr auto host_word_size = sizeof (host_address_t);
      static constexpr auto vm_word_size = sizeof (vm_address_t);

      /// Initialize the mmu with a base address.
      mmu(host_address_t);

      vm_address_t host_to_vm(host_address_t);
      host_address_t vm_to_host(vm_address_t);

      host_address_t base_ = 0;
    };

  } // namespace cpu

} // namespace nolimix86

#include <vm/mmu.hxx>
