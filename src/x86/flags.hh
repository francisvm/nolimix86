#pragma once

namespace nolimix86
{

  namespace x86
  {

    /// x86 EFLAGS
    enum flag : uint32_t
    {
      CF,
      OF,
      SF,
      ZF,
      AF,
      PF
    };

  } // namespace x86

} // namespace nolimix86

namespace std
{

  template <>
  struct hash<::nolimix86::x86::flag>
  {
    using argument_t = nolimix86::x86::flag;
    using result_t = size_t;

    result_t
    operator()(const argument_t& s) const
    {
      return static_cast<result_t>(s);
    }
  };

} // namespace std
