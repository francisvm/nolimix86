#pragma once

#include <iterator>

namespace nolimix86
{

  namespace cpu
  {

    template <typename T>
    struct memory
    {
      using size_type = size_t;

      memory(size_type);

      T* base();

      T& operator[](size_type);
      const T& operator[](size_type) const;

      size_type size_ = 0;
      std::unique_ptr<T[]> mem_ = nullptr;
    };

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
      stack(memory<T>&);

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
      memory<T>& mem_;
    };

    template <typename T>
    class heap
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
      heap(memory<T>&);

      size_type size() const;

      iterator begin();
      const_iterator begin() const;

      iterator end();
      const_iterator end() const;

      reference back();
      const_reference back() const;

      void alloc(T);

    private:
      size_type size_ = 0;
      memory<T>& mem_;
    };

  } // namespace cpu

} // namespace nolimix86

#include <vm/memory.hxx>
