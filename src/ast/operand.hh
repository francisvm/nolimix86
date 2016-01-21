#pragma once

#include <ast/ast.hh>
#include <ast/visitor.hh>
#include <x86/x86.hh>

#include <llvm/Support/raw_ostream.h>

#include <string>
#include <memory>

namespace nolimix86
{

  namespace ast
  {

    class operand : public ast
    {
      /// Operand tags
      public:
        struct temp_tag {};
        struct reg_tag {};
        struct imm_tag {};
        struct mem_tag {};
        struct label_tag {};

        enum class type
        {
          TEMP,
          REG,
          IMM,
          MEM,
          LABEL,
          UNKNOWN
        };

      public:
        operand() = default;

        /// Create an operand represented by a temporary.
        operand(size_t, temp_tag);

        /// Create an operand represented by a machine register.
        explicit operand(const std::string&, reg_tag = {});
        explicit operand(enum x86::reg, reg_tag = {});

        /// Create an operand represented by an immediate.
        explicit operand(size_t, imm_tag = {});

        /// Create an operand represented by a memory access.
        /// Arguments: offset, register.
        operand(size_t, const std::string&, mem_tag = {});

        /// Create an operand represented by an assembly label.
        operand(std::string, label_tag);

        type type_get() const;

        /// Handy functions.
        bool is_temp() const;
        bool is_reg() const;
        bool is_imm() const;
        bool is_mem() const;
        bool is_label() const;

        /// Print the operand.
        void dump(llvm::raw_ostream&) const;

        void accept(const_visitor&) const override;
        void accept(visitor&) override;

      private:

        struct impl
        {
          virtual void dump(llvm::raw_ostream&) const = 0;
        };

        /// The imlementation detail.
        std::unique_ptr<impl> impl_;
        type type_ = type::UNKNOWN;

        /// Implementation of the operand as a temporary.
        struct temp_impl : public impl
        {
          /// The number of the temporary.
          const size_t temp_num_ = 0;

          temp_impl(size_t);
          void dump(llvm::raw_ostream&) const override;
        };

        /// Implementation of the operand as a register.
        struct reg_impl : public impl
        {
          /// The register.
          const enum x86::reg reg_ = x86::UNKNOWN;

          reg_impl(const std::string&);
          reg_impl(enum x86::reg);
          void dump(llvm::raw_ostream&) const override;
        };

        /// Implementation of the operand as a immediate.
        struct imm_impl : public impl
        {
          /// The value of the immediate.
          const size_t value_ = 0;

          imm_impl(size_t);
          void dump(llvm::raw_ostream&) const override;
        };

        /// Implementation of the operand as a memory access.
        struct mem_impl : public impl
        {
          /// The value of the offset.
          const size_t offset_ = 0;

          /// The register.
          enum x86::reg reg_ = x86::UNKNOWN;

          mem_impl(size_t, const std::string&);
          void dump(llvm::raw_ostream&) const override;
        };

        /// Implementation of the operand as an assembly label.
        struct label_impl : public impl
        {
          /// The name of the labe.
          const std::string label_;

          label_impl(std::string);
          void dump(llvm::raw_ostream&) const override;
        };
    };

    template <typename Tag, typename... Args>
    operand make_operand(Args&&...);

  } // namespace ast

} // namespace nolimix86

#include <ast/operand.hxx>
