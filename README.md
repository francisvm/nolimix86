# nolimix86 [![CI Status](https://travis-ci.com/thegameg/nolimix86.svg?token=Gx9tcXtkVkqZjRSiMTiW&branch=dev)](https://travis-ci.com/thegameg/nolimix86)
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

# Goal
The goal of `nolimix86` is to simulate a virtual machine with unlimited
registers, called `temporaries` or `temps`.

So this is actually a pseudo x86 assembly, `%t0`, `%t1`, etc. as a register.

## Support

### Instructions
* `add`
* `call` [not implemented yet]
* `cmp`
* `idiv` [not implemented yet]
* `imul`
* `ja` [not implemented yet]
* `jae` [not implemented yet]
* `jb` [not implemented yet]
* `jbe` [not implemented yet]
* `je` [not implemented yet]
* `jg` [not implemented yet]
* `jge` [not implemented yet]
* `jl` [not implemented yet]
* `jle` [not implemented yet]
* `jmp` [not implemented yet]
* `jne` [not implemented yet]
* `js` [not implemented yet]
* `lea` [not implemented yet]
* `leave` [not implemented yet]
* `mov`
* `neg` [not implemented yet]
* `pop`
* `push`
* `ret` [not implemented yet]
* `sal` [not implemented yet]
* `sar` [not implemented yet]
* `sete` [not implemented yet]
* `sub`
* `test` [not implemented yet]

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
