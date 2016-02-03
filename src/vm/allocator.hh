#pragma once

#include <memory>

namespace nolimix86
{

  namespace vm
  {

    template <typename T>
    class vm_stack_allocator
    {
    public:
      using value_type = T;
      using pointer = value_type*;
      using size_type = size_t;

    private:
      static constexpr size_type default_size = 4096;

    public:

      vm_stack_allocator(size_type size = default_size);

      vm_stack_allocator(const vm_stack_allocator&) = delete;
      vm_stack_allocator& operator=(const vm_stack_allocator&) = delete;

      vm_stack_allocator(vm_stack_allocator&&) = default;
      vm_stack_allocator& operator=(vm_stack_allocator&&) = default;

      pointer allocate(size_type);

      void deallocate(pointer, size_type);

    private:
      size_type size_;
      size_type capacity_;
      std::unique_ptr<T[]> mem_ = nullptr;
    };

  } // namespace str

} // namespace nolimix86

#include <vm/allocator.hxx>
