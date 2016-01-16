#pragma once

#include <common.hh>
#include <misc/meta.hh>

namespace nolimix86
{

  namespace x86
  {

    /// x86 instructions handled by nolimix86
    enum x86 : opcode_t
    {
      ADD,
      CALL,
      CMP,
      IDIV,
      IMUL,
      JA,
      JAE,
      JB,
      JBE,
      JE,
      JG,
      JGE,
      JL,
      JLE,
      JMP,
      JNE,
      JS,
      LEA,
      LEAVE,
      MOV,
      NEG,
      POP,
      PUSH,
      RET,
      SAL,
      SAR,
      SETE,
      SUB,
      TEST
    };

    /// A ranges of llvm instructions corresponding to the instruction
    /// mnemonic.
    using add = range<75, 157, ADD>;
    using call = range<376, 385, CALL>;
    using cmp = range<556, 622, CMP>;
    using idiv = range<902, 910, IDIV>;
    using imul = range<922, 947, IMUL>;
    using ja = range<1100, 1103, JA>;
    using jae = range<1097, 1100, JAE>;
    using jb = range<1106, 1109, JB>;
    using jbe = range<1103, 1105, JBE>;
    using je = range<1111, 1114, JE>;
    using jg = range<1117, 1120, JG>;
    using jge = range<1114, 1117, JGE>;
    using jl = range<1123, 1126, JL>;
    using jle = range<1120, 1123, JLE>;
    using jmp = range<1126, 1135, JMP>;
    using jne = range<1135, 1138, JNE>;
    using js = range<1154, 1157, JS>;
    using lea = range<1267, 1271, LEA>;
    using leave = range<1271, 1273, LEAVE>;
    using mov = range<1627, 1821, MOV>;
    using neg = range<1870, 1878, NEG>;
    using pop = range<2171, 2203, POP>;
    using push = range<2289, 2323, PUSH>;
    using ret = range<2455, 2461, RET>;
    using sal = range<2664, 2704, SAL>;
    using sar = range<2532, 2560, SAR>;
    using sete = range<2622, 2624, SETE>;
    using sub = range<2814, 2900, SUB>;
    using test = range<2927, 2947, TEST>;

    /// Type list of all possible ranges.
    using x86_set = ranges<add, call, cmp, idiv, imul, ja, jae, jb, jbe, je, jg,
                           jge, jl, jle, jmp, jne, js, lea, leave, mov, neg,
                           pop, push, ret, sal, sar, sete, sub, test>;

  } // namespace ast

} // namespace nolimix86
