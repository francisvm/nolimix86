# nolimix86
x86 virtual machine with unlimited registers

# Build

## Dependencies

* CMake (2.8.12.2+)
* LLVM  (3.8local)

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
* `call`
* `cmp`
* `idiv`
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
* `lea`
* `leave`
* `mov`
* `neg`
* `pop`
* `push`
* `ret`
* `sal`
* `sar`
* `sete`
* `sub`
* `test`

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
