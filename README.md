# Tiny CPU

A 8-bit CPU emulator and assembler written in C.

The project implements a small custom instruction set and simulates the fetch-decode-execute cycle of a CPU. Assembly programs are translated into raw 8-bit machine code by the assembler and then loaded and executed by the CPU emulator.

## Features

- 8-bit CPU
- 4 general-purpose registers (R0-R3)
- 256 bytes of memory
- 8-bit program counter
- 8-bit fixed-width instructions
- Custom assembler
- Binary program loader
- Fetch-decode-execute cycle
- Debug trace showing executed instructions
- Unified instruction and data memory

## Instruction Set

The CPU supports eight instructions:

| Instruction | Description |
|-------------|-------------|
| HALT | Stop execution |
| ADD | Add two registers |
| SUB | Subtract two registers |
| AND | Bitwise AND |
| OR | Bitwise OR |
| LOAD | Load a value from memory |
| STORE | Store a value into memory |
| JUMP | Jump to a memory address |

See `ISA.md` for the full instruction encoding and behavior.

## Files

- `cpu.c` - CPU emulator
- `assembler.c` - assembler
- `program.asm` - example assembly program
- `ISA.md` - instruction set architecture documentation
- `program.bin` - assembled machine-code program

## Building

Compile the CPU emulator:

```bash
gcc -Wall -Wextra -std=c99 cpu.c -o tinycpu
