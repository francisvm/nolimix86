#pragma once

#include <common.hh>

namespace nolimix86
{
  /// A range instance definition.
  template <size_t start_in, size_t end_in, opcode_t opcode_in>
  struct range
  {
    static constexpr auto start = start_in;
    static constexpr auto end = end_in;
    static constexpr auto opcode = opcode_in;
  };

  /// A range instance list
  template <typename... Ranges>
  struct ranges
  {
  };

  /// Find opcode inside the type list.
  template <typename... Ranges>
  struct find_range_impl;

  /// If it can't be found, try the next range.
  template <typename Range, typename... Ranges>
  struct find_range_impl<Range, Ranges...>
  {
    auto
    operator()(size_t i)
    {
      return i >= Range::start && i < Range::end
               ? Range::opcode
               : find_range_impl<Ranges...>{}(i);
    }
  };

  /// Stop and return 0 if it's not to be found.
  template <>
  struct find_range_impl<>
  {
    opcode_t
    operator()(size_t)
    {
      return 0;
    }
  };

  /// Unpack the Ranges parameters.
  template <typename Range>
  struct find_range;

  template <template<typename...> class Range, typename... Ranges>
  struct find_range<Range<Ranges...>>
  {
    auto
    operator()(size_t i)
    {
      return find_range_impl<Ranges...>{}(i);
    }
  };

  template <typename Range>
  opcode_t
  find_opcode(size_t i)
  {
    return find_range<Range>{}(i);
  }

} // namespace nolimix86
