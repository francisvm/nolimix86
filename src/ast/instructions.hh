#pragma once

#include <x86/x86.hh>
#include <ast/instr.hh>

// :( Sorry.
#define ACCEPT_VISITOR                                                         \
public:                                                                        \
  void accept(const_visitor& v) const override                                 \
  {                                                                            \
    v(*this);                                                                  \
  }                                                                            \
                                                                               \
  void accept(visitor& v) override                                             \
  {                                                                            \
    v(*this);                                                                  \
  }

namespace nolimix86
{

  namespace ast
  {
    class add : public instr<x86::ADD, 2>
    {
      ACCEPT_VISITOR
    };

    class call : public instr<x86::CALL, 1>
    {
      ACCEPT_VISITOR
    };

    class cmp : public instr<x86::CMP, 2>
    {
      ACCEPT_VISITOR
    };

    class idiv : public instr<x86::IDIV, 2>
    {
      ACCEPT_VISITOR
    };

    class imul : public instr<x86::IMUL, 2>
    {
      ACCEPT_VISITOR
    };

    class ja : public instr<x86::JA, 1>
    {
      ACCEPT_VISITOR
    };

    class jae : public instr<x86::JAE, 1>
    {
      ACCEPT_VISITOR
    };

    class jb : public instr<x86::JB, 1>
    {
      ACCEPT_VISITOR
    };

    class jbe : public instr<x86::JBE, 1>
    {
      ACCEPT_VISITOR
    };

    class je : public instr<x86::JE, 1>
    {
      ACCEPT_VISITOR
    };

    class jg : public instr<x86::JG, 1>
    {
      ACCEPT_VISITOR
    };

    class jge : public instr<x86::JGE, 1>
    {
      ACCEPT_VISITOR
    };

    class jl : public instr<x86::JL, 1>
    {
      ACCEPT_VISITOR
    };

    class jle : public instr<x86::JLE, 1>
    {
      ACCEPT_VISITOR
    };

    class jmp : public instr<x86::JMP, 1>
    {
      ACCEPT_VISITOR
    };

    class jne : public instr<x86::JNE, 1>
    {
      ACCEPT_VISITOR
    };

    class js : public instr<x86::JS, 1>
    {
      ACCEPT_VISITOR
    };

    class lea : public instr<x86::LEA, 2>
    {
      ACCEPT_VISITOR
    };

    class leave : public instr<x86::LEAVE, 0>
    {
      ACCEPT_VISITOR
    };

    class mov : public instr<x86::MOV, 2>
    {
      ACCEPT_VISITOR
    };

    class neg : public instr<x86::NEG, 1>
    {
      ACCEPT_VISITOR
    };

    class pop : public instr<x86::POP, 1>
    {
      ACCEPT_VISITOR
    };

    class push : public instr<x86::PUSH, 1>
    {
      ACCEPT_VISITOR
    };

    class ret : public instr<x86::RET, 1>
    {
      ACCEPT_VISITOR
    };

    class sal : public instr<x86::SAL, 2>
    {
      ACCEPT_VISITOR
    };

    class sar : public instr<x86::SAR, 2>
    {
      ACCEPT_VISITOR
    };

    class sete : public instr<x86::SETE, 2>
    {
      ACCEPT_VISITOR
    };

    class sub : public instr<x86::SUB, 2>
    {
      ACCEPT_VISITOR
    };

    class test : public instr<x86::TEST, 2>
    {
      ACCEPT_VISITOR
    };

  } // namespace ast

} // namespace nolimix86

#undef ACCEPT_VISITOR
