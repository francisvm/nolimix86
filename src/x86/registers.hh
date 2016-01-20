#pragma once

#include <common.hh>

#include <map>

namespace nolimix86
{

  namespace x86
  {

    /// x86 common-used registers
    enum reg : uint8_t
    {
      // Shouldn never have to use this, since LLVM parses x86 correctly.
      UNKNOWN = 0,
      EAX,
      EBX,
      ECX,
      EDI,
      ESI,
      ESP,
      EBP
    };

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

      return UNKNOWN;
    }

    inline
    std::string
    reg_convert(enum reg reg)
    {
      auto it = rev_reg_map.find(reg);
      if (it != rev_reg_map.end())
        return it->second;

      return "";
    }

    constexpr auto max_valid_reg = 246U;

  } // namespace x86

} // namespace nolimix86
