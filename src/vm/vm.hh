#pragma once

#include <ast/default-visitor.hh>
#include <vm/cpu.hh>

#include <vector>

#include <experimental/optional>

namespace nolimix86
{

  namespace vm
  {

    template <typename Cpu>
    class vm : ast::const_default_visitor
    {
      public:
        using super_type = ast::const_default_visitor;
        using super_type::operator();

        using cpu_t = Cpu;
        using program_t = ast::program;
        using ip_t = program_t::const_iterator;

        /// Get the vm's cpu.
        const cpu_t& cpu_get() const;

        void operator()(const ast::add&) override;

        void operator()(const ast::call&) override;

        void operator()(const ast::cmp&) override;

        void operator()(const ast::idiv&) override;

        void operator()(const ast::imul&) override;

        void operator()(const ast::ja&) override;

        void operator()(const ast::jae&) override;

        void operator()(const ast::jb&) override;

        void operator()(const ast::jbe&) override;

        void operator()(const ast::je&) override;

        void operator()(const ast::jg&) override;

        void operator()(const ast::jge&) override;

        void operator()(const ast::jl&) override;

        void operator()(const ast::jle&) override;

        void operator()(const ast::jmp&) override;

        void operator()(const ast::jne&) override;

        void operator()(const ast::js&) override;

        void operator()(const ast::lea&) override;

        void operator()(const ast::leave&) override;

        void operator()(const ast::mov&) override;

        void operator()(const ast::neg&) override;

        void operator()(const ast::pop&) override;

        void operator()(const ast::push&) override;

        void operator()(const ast::ret&) override;

        void operator()(const ast::sal&) override;

        void operator()(const ast::sar&) override;

        void operator()(const ast::sete&) override;

        void operator()(const ast::sub&) override;

        void operator()(const ast::test&) override;

        void operator()(const ast::program&) override;

      private:
        cpu_t cpu_;
        ip_t eip_;

        // Jump to a label
        void jump_to(const ast::operand::label_t&);
    };

    using x86 = vm<cpu::x86>;

  } // namespace vm

} // namespace nolimix86

#include <vm/vm.hxx>
