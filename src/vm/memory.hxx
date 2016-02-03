#pragma once

#include <vm/memory.hh>

namespace nolimix86
{

  namespace cpu
  {

    template <typename T>
    stack<T>::stack(T* mem)
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
      return typename stack<T>::iterator{mem_ + size_};
    }

    template <typename T>
    typename stack<T>::const_iterator
    stack<T>::begin() const
    {
      return typename stack<T>::iterator{mem_ + size_};
    }

    template <typename T>
    typename stack<T>::iterator
    stack<T>::end()
    {
      return typename stack<T>::iterator{mem_};
    }

    template <typename T>
    typename stack<T>::const_iterator
    stack<T>::end() const
    {
      return typename stack<T>::iterator{mem_};
    }

    template <typename T>
    void
    stack<T>::push(T elt)
    {
      mem_[size_] = std::move(elt);
      ++size_;
    }

    template <typename T>
    void
    stack<T>::pop()
    {
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
    heap<T>::heap(T* mem)
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
      return typename heap<T>::iterator{mem_};
    }

    template <typename T>
    typename heap<T>::const_iterator
    heap<T>::begin() const
    {
      return typename heap<T>::iterator{mem_};
    }

    template <typename T>
    typename heap<T>::iterator
    heap<T>::end()
    {
      return typename heap<T>::iterator{mem_ - size_};
    }

    template <typename T>
    typename heap<T>::const_iterator
    heap<T>::end() const
    {
      return typename heap<T>::iterator{mem_ - size_};
    }

    template <typename T>
    void
    heap<T>::alloc(T elt)
    {
      *(mem_ - size_ - 1) = std::move(elt);
      ++size_;
    }

    template <typename T>
    typename heap<T>::reference
    heap<T>::back()
    {
      return *(mem_ - size_ - 1);
    }

    template <typename T>
    typename heap<T>::const_reference
    heap<T>::back() const
    {
      return *(mem_ - size_ - 1);
    }

  } // namespace cpu

} // namespace nolimix86
