# nolimix86 [![Build Status](https://travis-ci.org/thegameg/nolimix86.svg?branch=master)](https://travis-ci.org/thegameg/nolimix86)
x86 virtual machine with unlimited registers

# Build

## Dependencies

* CMake (2.8.12.2+)
* LLVM  (3.8local)
* Google Test (`libgtest`) (1.7.0+)

### Building

```
mkdir build
cd build
cmake .. -G Ninja # if you want to use ninja
ninja nolimix86
```

A binary `nolimix86` is built in `build/bin`.

### Usage

`nolimix86 [options] <input file>`

`nolimix86 --help` for more options.

`nolimix86 -A` to dump the parsed program on `stdout`.

`nolimix86 -Y` to dump the cpu's state at the end of the program
(in YAML format).

# Goal

The goal of `nolimix86` is to simulate a virtual machine with unlimited
registers, called `temporaries` or `temps` (or `virtual registers` in LLVM).

So this is actually a pseudo x86 assembly, using `%t0`, `%t1`, etc. as valid
registers.

This virtual machine is running the code directly from the AST, and can't
actually encode and map the code in memory, since there is no valid encoding
for `%t#` registers.

The syntax is based on the AT&T x86 assembly and is parsed using a modified
version of LLVM's x86AsmParser, that can be found
[here](https://github.com/thegameg/llvm).

This following modifications were applied:

* `X86AsmParser.cpp`: Handle `%t#` registers in the lexer.
* `X86Operand.h`: Handle `%t#` registers as general purpose registers,
    allowing compatibility between general purpose registers and temporaries.

Here is a simple example of a valid pseudo x86 assembly code:

```
  .text
l0:
  movl $1, %t1
  movl %t1, %t2
  addl $2, %t2
  push $42
  pop %eax
  push $101
  ret
```

Here is the output of `nolimix86 -Y`, dumping the state of the CPU at the end
of the program:

```
---
cpu:             x86
registers:       
  - name:            t2
    value:           3
  - name:            t1
    value:           1
  - name:            ebp
    value:           0
  - name:            esi
    value:           0
  - name:            esp
    value:           4
  - name:            eax
    value:           42
  - name:            ebx
    value:           0
  - name:            ecx
    value:           0
  - name:            edi
    value:           0
flags:           
  - name:            pf
    value:           0
  - name:            af
    value:           0
  - name:            cf
    value:           0
  - name:            of
    value:           0
  - name:            sf
    value:           0
  - name:            zf
    value:           0
...
```

## Support

### Instructions
* `add`
* `call`
* `cmp`
* `idiv`    \[VM\]\[not implemented yet]
* `imul`
* `ja`
* `jae`
* `jb`
* `jbe`
* `je`
* `jg`
* `jge`
* `jl`
* `jle`
* `jmp`
* `jne`
* `js`
* `lea`     \[VM\]\[not implemented yet]
* `leave`
* `mov`
* `neg`     \[VM\]\[not implemented yet]
* `pop`
* `push`
* `ret`
* `sal`     \[VM\]\[not implemented yet]
* `sar`     \[VM\]\[not implemented yet]
* `sete`    \[VM\]\[not implemented yet]
* `sub`
* `test`    \[VM\]\[not implemented yet]
* `inc`     \[AST\]\[VM\]\[not implemented yet]
* `dec`     \[AST\]\[VM\]\[not implemented yet]
* `or`      \[AST\]\[VM\]\[not implemented yet]
* `and`     \[AST\]\[VM\]\[not implemented yet]
* `xor`     \[AST\]\[VM\]\[not implemented yet]

### Registers

* `eax`
* `ebp`
* `ebx`
* `ecx`
* `edi`
* `edx`
* `esi`
* `esp`
* `t[0-9]+`

# Misc

## Sanitizers

In order to build with the sanitizers on, pass the following flags to CMake.

* `-DNOLIMIX86_ASAN` for ASAN -> `./bin/nolimix86-asan`
* `-DNOLIMIX86_MSAN` for MSAN -> `./bin/nolimix86-msan`
* `-DNOLIMIX86_UBSAN` for UBSAN -> `./bin/nolimix86-ubsan`
* `-DNOLIMIX86_LSAN` for LSAN -> `./bin/nolimix86-lsan`

# Internals

## Parsing

### Parser

* Parsing is done using the `llvm::X86AsmParser`.
* A subclass of `llvm::MCELFStreamer` is creating an ast using various hacks
  in order to detect the correct x86 instruction to create. Most of the
  instructions opcodes are declared in `src/x86/instructions.hh`, allowing
  a range of MC opcodes to bind to a specific instructions, without minding
  the operands types.

### AST

* The AST consists in a basic hierarchy which is visitable through the `accept`
  member function.

* All the AST walks are done using visitors and using the `default_visitor` as
  a base class.

* The apply visitor allows us to workaround the fact that no virtual method
  can be templated. It takes a class defining the `visit` function and calls
  it with every node. It allows the visitor to be generic for all the
  instructions, depending on their operand count.

## VM

### Visitor

* The VM is an AST visitor. The final AST being a list of instructions,
  the VM is using an iterator as the `instruction pointer`, called `eip` on
  x86.

* The VM is a template class containing a CPU, that handles all the memory
  and register/flags access.

* All the memory accesses go through the `cpu::mmu` template class,
  which translates host < -- > vm addresses, depending on the CPU.

### Stack and Heap

* The stack and the heap are basically wrappers around a big allocated memory
  that is accessed through the `cpu::mmu`.

* The CPU owns a stack, a heap, pointing to a global memory.

### CPU

* Registers -> `std::unordered_map<reg_t, word_t>`.
* Flags     -> `std::unordered_map<flag_t, word_t>`.
* Globals   -> `std::unordered_map<std::string, word_t>`. (global symbols).
* Memory    -> `char[]`.
* MMU       -> `cpu::mmu`.
* Stack     -> `cpu::stack` going through the MMU to access the Memory.
* Heap      -> `cpu::heap` going through the MMU to access the Memory.

## Testing

* Most of the testing goes through parsing -> dumping -> diff.

* Behaviour testing is done using the `-Y` option, by dumping the current CPU
  state of the program. This allows checking the expected state of a particular
  program.
