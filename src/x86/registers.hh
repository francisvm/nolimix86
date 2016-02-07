#pragma once

#include <common.hh>

#include <string>
#include <map>

namespace nolimix86
{

  namespace x86
  {

    /// x86 common-used registers
    enum reg : uint32_t
    {
      // Shouldn never have to use this, since LLVM parses x86 correctly.
      UNKNOWN = 0,
      EAX = 19,
      EBX = 21,
      ECX = 22,
      EDI = 23,
      ESI = 29,
      ESP = 30,
      EBP = 20
    };

    constexpr auto max_valid_reg = 246U;

    // Use operator""s for strings.
    using namespace std::string_literals;

    static std::map<std::string, enum reg> reg_map
    {
      { "eax"s, EAX },
      { "ebx"s, EBX },
      { "ecx"s, ECX },
      { "edi"s, EDI },
      { "esi"s, ESI },
      { "esp"s, ESP },
      { "ebp"s, EBP }
    };

    static std::map<enum reg, std::string> rev_reg_map
    {
      { EAX, "eax"s },
      { EBX, "ebx"s },
      { ECX, "ecx"s },
      { EDI, "edi"s },
      { ESI, "esi"s },
      { ESP, "esp"s },
      { EBP, "ebp"s }
    };

    inline
    enum reg
    reg_convert(const std::string& reg_name)
    {
      auto it = reg_map.find(reg_name);
      if (it != reg_map.end())
        return it->second;

      if (reg_name[0] == 't')
      {
        auto pp_reg_name = std::string{std::next(reg_name.begin()),
                                       reg_name.end()};
        auto reg_no = std::stoi(pp_reg_name);

        return static_cast<enum reg>(max_valid_reg + reg_no);
      }

      return UNKNOWN;
    }

    inline
    std::string
    reg_convert(enum reg reg)
    {
      auto it = rev_reg_map.find(reg);
      if (it != rev_reg_map.end())
        return it->second;

      if (static_cast<decltype(max_valid_reg)>(reg) >= max_valid_reg)
      {
        auto temp = reg - max_valid_reg;
        return "t"s + std::to_string(temp);
      }

      return "";
    }

  } // namespace x86

} // namespace nolimix86

namespace std
{

  template <>
  struct hash<::nolimix86::x86::reg>
  {
    using argument_t = nolimix86::x86::reg;
    using result_t = size_t;

    result_t
    operator()(const argument_t& s) const
    {
      return static_cast<result_t>(s);
    }
  };

} // namespace std
