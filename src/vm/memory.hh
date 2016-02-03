#pragma once

#include <iterator>

namespace nolimix86
{

  namespace cpu
  {

    template <typename T>
    class stack
    {
    public:
      using value_type = T;
      using reference = T&;
      using const_reference = const T&;
      using pointer = value_type*;
      using const_pointer = const value_type*;
      using size_type = size_t;
      using iterator = std::reverse_iterator<pointer>;
      using const_iterator = std::reverse_iterator<const_pointer>;

    public:
      stack(T*);

      stack(const stack&) = delete;
      stack& operator=(const stack&) = delete;

      stack(stack&&) = default;
      stack& operator=(stack&&) = default;

      size_type size() const;

      iterator begin();
      const_iterator begin() const;

      iterator end();
      const_iterator end() const;

      reference back();
      const_reference back() const;

      void push(T);

      void pop();

    private:
      size_type size_ = 0;
      T* mem_ = nullptr;
    };

  } // namespace cpu

} // namespace nolimix86

#include <vm/memory.hxx>
