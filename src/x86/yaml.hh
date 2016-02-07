#include <vm/cpu.hh>

#include <llvm/Support/YAMLTraits.h>

#include <utility>
#include <unordered_map>
#include <string>

namespace llvm
{

  namespace yaml
  {

    namespace cpu = nolimix86::cpu;

    using cpu_t = cpu::x86;
    using regs_t = std::unordered_map<cpu_t::reg_t, cpu_t::word_t>;
    using reg_t = std::pair<cpu_t::reg_t, cpu_t::word_t>;
    using flags_t = std::unordered_map<cpu_t::flag_t, cpu_t::word_t>;
    using flag_t = std::pair<cpu_t::flag_t, cpu_t::word_t>;

    template <>
    struct ScalarEnumerationTraits<cpu_t::flag_t>
    {
      static
      void
      enumeration(IO& io, cpu_t::flag_t& value)
      {
        io.enumCase(value, "cf", cpu_t::flag_t::CF);
        io.enumCase(value, "of", cpu_t::flag_t::OF);
        io.enumCase(value, "sf", cpu_t::flag_t::SF);
        io.enumCase(value, "zf", cpu_t::flag_t::ZF);
        io.enumCase(value, "af", cpu_t::flag_t::AF);
        io.enumCase(value, "pf", cpu_t::flag_t::PF);
      }

    };

    template <>
    struct ScalarTraits<cpu_t::reg_t>
    {
      static
      void
      output(const cpu_t::reg_t& value, void*, llvm::raw_ostream& out)
      {
        out << nolimix86::x86::reg_convert(value);
      }

      static
      StringRef
      input(StringRef scalar, void*, cpu_t::reg_t& reg)
      {
        auto converted = nolimix86::x86::reg_convert(scalar);
        if (converted == nolimix86::x86::UNKNOWN)
          return "Unable to parse register";

        reg = converted;
        return "";
      }

      static
      bool
      mustQuote(StringRef)
      {
        return false;
      }
    };

    template <>
    struct SequenceTraits<regs_t>
    {
      static
      size_t
      size(IO&, regs_t& regs)
      {
        return regs.size();
      }

      static
      reg_t&
      element(IO&, regs_t& regs, size_t index)
      {
        auto it = std::next(regs.begin(), index);
        // Cast the `const` of the key away.
        auto ptr = reinterpret_cast<reg_t*>(&*it);
        return *ptr;
      }
    };

    template <>
    struct SequenceTraits<flags_t>
    {
      static
      size_t
      size(IO&, flags_t& flags)
      {
        return flags.size();
      }

      static
      flag_t&
      element(IO&, flags_t& flags, size_t index)
      {
        auto it = std::next(flags.begin(), index);
        // Cast the `const` of the key away.
        auto ptr = reinterpret_cast<flag_t*>(&*it);
        return *ptr;
      }
    };

    template <>
    struct MappingTraits<flag_t>
    {
      static
      void
      mapping(IO& io, flag_t& elt)
      {
        io.mapRequired("name", elt.first);
        io.mapRequired("value", elt.second);
      }
    };

    template <>
    struct MappingTraits<reg_t>
    {
      static
      void
      mapping(IO& io, reg_t& elt)
      {
        io.mapRequired("name", elt.first);
        io.mapRequired("value", elt.second);
      }
    };

    template <>
    struct MappingTraits<cpu_t>
    {
      static
      void
      mapping(IO& io, cpu_t& cpu)
      {
        auto name = std::string{cpu_t::name};
        io.mapRequired("cpu", name);
        io.mapRequired("registers", cpu.regs_);
        io.mapRequired("flags", cpu.eflags_);
      }
    };

  } // namespace llvm

} // namespace yaml

namespace nolimix86
{

  namespace x86
  {

  } // namespace x86

} // namespace nolimix86
