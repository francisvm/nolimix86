#pragma once

#include <common.hh>

namespace nolimix86
{

  namespace ast
  {

    class ast;

    template <template <typename> class Const>
    class visitor_impl;

    class instr_base;

    template <opcode_t opcode, size_t operands_count>
    class instr;

    class operand;

    class add;

    class call;

    class cmp;

    class idiv;

    class imul;

    class ja;

    class jae;

    class jb;

    class jbe;

    class je;

    class jg;

    class jge;

    class jl;

    class jle;

    class jmp;

    class jne;

    class js;

    class lea;

    class leave;

    class mov;

    class neg;

    class pop;

    class push;

    class ret;

    class sal;

    class sar;

    class sete;

    class sub;

    class test;

    class basic_block;

  } // namespace ast

} // namespace nolimix86
