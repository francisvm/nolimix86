#pragma once

#include <ast/ast.hh>
#include <ast/fwd.hh>
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
        struct symbol_tag {};

        enum class type
        {
          TEMP,
          REG,
          IMM,
          MEM,
          LABEL,
          SYMBOL,
          UNKNOWN
        };

      public:
        using temp_t = uint32_t;
        using reg_t = enum x86::reg;
        using imm_t = size_t;
        operand() = default;

        /// Create an operand represented by a temporary.
        operand(temp_t, temp_tag);

        /// Create an operand represented by a machine register.
        explicit operand(const std::string&, reg_tag = {});
        explicit operand(reg_t, reg_tag = {});

        /// Create an operand represented by an immediate.
        explicit operand(imm_t, imm_tag = {});

        /// Create an operand represented by a memory access.
        /// Arguments: offset, register.
        operand(imm_t, const std::string&, mem_tag = {});
        operand(imm_t, reg_t, mem_tag = {});

        /// Create an operand represented by an assembly label.
        operand(const basic_block&, label_tag = {});

        /// Create an operand represented by a symbol
        operand(std::string, symbol_tag = {});

        type type_get() const;

        /// Temp accessors.
        bool is_temp() const;
        temp_t temp_get() const;
        reg_t temp_reg_get() const;

        /// Registers accessors.
        bool is_reg() const;
        reg_t reg_get() const;

        /// Immediates accessors.
        bool is_imm() const;
        imm_t imm_get() const;

        /// Memory accessors.
        bool is_mem() const;
        reg_t mem_reg_get() const;
        imm_t mem_offset_get() const;

        /// Label accessors.
        bool is_label() const;
        const basic_block& label_bb_get() const;

        /// Symbol accessors.
        bool is_symbol() const;
        const std::string& symbol_get() const;

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
          const temp_t temp_num_ = 0;

          temp_impl(temp_t);
          void dump(llvm::raw_ostream&) const override;
        };

        /// Implementation of the operand as a register.
        struct reg_impl : public impl
        {
          /// The register.
          const reg_t reg_ = x86::UNKNOWN;

          reg_impl(const std::string&);
          reg_impl(reg_t);
          void dump(llvm::raw_ostream&) const override;
        };

        /// Implementation of the operand as a immediate.
        struct imm_impl : public impl
        {
          /// The value of the immediate.
          const imm_t value_ = 0;

          imm_impl(imm_t);
          void dump(llvm::raw_ostream&) const override;
        };

        /// Implementation of the operand as a memory access.
        struct mem_impl : public impl
        {
          /// The value of the offset.
          const imm_t offset_ = 0;

          /// The register.
          reg_t reg_ = x86::UNKNOWN;

          mem_impl(imm_t, const std::string&);
          mem_impl(imm_t, reg_t);
          void dump(llvm::raw_ostream&) const override;
        };

        /// Implementation of the operand as an assembly label.
        struct label_impl : public impl
        {
          /// The label with the basic block.
          const basic_block& bb_;

          label_impl(const basic_block&);
          void dump(llvm::raw_ostream&) const override;
        };

        /// Implementation of the operand as a symbol
        struct symbol_impl : public impl
        {
          /// The symbol's name.
          std::string name_;

          symbol_impl(std::string);
          void dump(llvm::raw_ostream&) const override;
        };

    };

    template <typename Tag, typename... Args>
    operand make_operand(Args&&...);

  } // namespace ast

} // namespace nolimix86

#include <ast/operand.hxx>
