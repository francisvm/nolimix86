#pragma once

#include <vm/memory.hh>
#include <common.hh>

#include <cstdlib>

namespace nolimix86
{

  namespace cpu
  {

    template <typename T>
    memory<T>::memory(size_type size)
      : size_{size}
      , mem_{std::make_unique<T[]>(size)}
    {
    }

    template <typename T>
    T*
    memory<T>::base()
    {
      return mem_.get();
    }

    template <typename T>
    T&
    memory<T>::operator[](size_type i)
    {
      return mem_[i];
    }

    template <typename T>
    const T&
    memory<T>::operator[](size_type i) const
    {
      return mem_[i];
    }

    template <typename T>
    stack<T>::stack(memory<T>& mem)
      : size_{0}
      , mem_{mem}
    {
    }

    template <typename T>
    typename stack<T>::size_type
    stack<T>::size() const
    {
      return size_;
    }

    template <typename T>
    typename stack<T>::iterator
    stack<T>::begin()
    {
      return typename stack<T>::iterator{mem_.base() + size_};
    }

    template <typename T>
    typename stack<T>::const_iterator
    stack<T>::begin() const
    {
      return typename stack<T>::iterator{mem_.base() + size_};
    }

    template <typename T>
    typename stack<T>::iterator
    stack<T>::end()
    {
      return typename stack<T>::iterator{mem_.base()};
    }

    template <typename T>
    typename stack<T>::const_iterator
    stack<T>::end() const
    {
      return typename stack<T>::iterator{mem_.base()};
    }

    template <typename T>
    void
    stack<T>::push(T elt)
    {
      if (size_ > mem_.size_)
        die("Out of memory.");

      mem_[size_] = std::move(elt);
      ++size_;
    }

    template <typename T>
    void
    stack<T>::pop()
    {
      if (size_ == 0)
        die("Stack is empty.");

      size_--;
    }

    template <typename T>
    typename stack<T>::reference
    stack<T>::back()
    {
      return mem_[size_ - 1];
    }

    template <typename T>
    typename stack<T>::const_reference
    stack<T>::back() const
    {
      return mem_[size_ - 1];
    }

    template <typename T>
    heap<T>::heap(memory<T>& mem)
      : size_{0}
      , mem_{mem}
    {
    }

    template <typename T>
    typename heap<T>::size_type
    heap<T>::size() const
    {
      return size_;
    }

    template <typename T>
    typename heap<T>::iterator
    heap<T>::begin()
    {
      return typename heap<T>::iterator{mem_.base() + mem_.size_};
    }

    template <typename T>
    typename heap<T>::const_iterator
    heap<T>::begin() const
    {
      return typename heap<T>::iterator{mem_.base() + mem_.size_};
    }

    template <typename T>
    typename heap<T>::iterator
    heap<T>::end()
    {
      return typename heap<T>::iterator{mem_.base()};
    }

    template <typename T>
    typename heap<T>::const_iterator
    heap<T>::end() const
    {
      return typename heap<T>::iterator{mem_.base()};
    }

    template <typename T>
    void
    heap<T>::alloc(T elt)
    {
      if (size_ > mem_.size_)
        die("Out of memory.");

      *(mem_.base() + mem_.size_ - size_ - 1) = std::move(elt);
      ++size_;
    }

    template <typename T>
    typename heap<T>::reference
    heap<T>::back()
    {
      return *(mem_.base() + mem_.size_ - size_ - 1);
    }

    template <typename T>
    typename heap<T>::const_reference
    heap<T>::back() const
    {
      return *(mem_.base() + mem_.size_ - size_ - 1);
    }

  } // namespace cpu

} // namespace nolimix86
