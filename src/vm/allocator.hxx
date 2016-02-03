#pragma once

#include <vm/allocator.hh>

#include <iostream>
#include <cassert>

namespace nolimix86
{

  namespace vm
  {

    template <typename T>
    vm_stack_allocator<T>::vm_stack_allocator(size_type capacity)
      : size_{0}
      , capacity_{capacity}
      , mem_{std::make_unique<T[]>(capacity)}
    {
    }

    template <typename T>
    typename vm_stack_allocator<T>::pointer
    vm_stack_allocator<T>::allocate(typename vm_stack_allocator<T>::size_type
                                    size)
    {
      assert(size_ <= capacity_);

      const auto tmp = mem_.get() + size_;
      size_ += size;
      return tmp;
    }

    template <typename T>
    void
    vm_stack_allocator<T>::deallocate(typename vm_stack_allocator<T>::pointer,
                                      typename vm_stack_allocator<T>::size_type)
    {
    }

  } // namespace vm

} // namespace nolimix86
