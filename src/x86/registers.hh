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

    inline
    enum reg reg_convert(const std::string& reg_name)
    {
      auto it = reg_map.find(reg_name);
      if (it != reg_map.end())
        return it->second;

      return UNKNOWN;
    }

  } // namespace ast

} // namespace nolimix86
