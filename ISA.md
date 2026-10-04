# Tiny CPU ISA

## CPU Specifications

- 8-bit CPU
- 4 general-purpose registers: R0-R3
- 256 bytes of memory
- 8-bit program counter
- 8-bit instructions
- Unified instruction and data memory

## Instruction Format

Each instruction is 8 bits:

`[ opcode (3 bits) ][ RegA (2 bits) ][ RegB (2 bits) ][ unused (1 bit) ]`

Bit positions:

`[ 7 6 5 ][ 4 3 ][ 2 1 ][ 0 ]`

## Opcodes

| Binary | Instruction |
|--------|-------------|
| 000    |     HALT    |
| 001    |     ADD     |
| 010    |     SUB     |
| 011    |     AND     |
| 100    |     OR      |
| 101    |     LOAD    |
| 110    |     STORE   |
| 111    |     JUMP    |

## Register Encoding

| Binary | Register |
|--------|----------|
| 00     |    R0    |
| 01     |    R1    |
| 10     |    R2    |
| 11     |    R3    |

## Instructions

### HALT

Stops execution of the CPU.

Example:

`HALT`

Encoding:

`000 00 00 0`

### ADD

`ADD RegA RegB`

Performs:

`RegA = RegA + RegB`

Example:

`ADD R2 R1`

Encoding:

`001 10 01 0` → `00110010` → `0x32`

### SUB

`SUB RegA RegB`

Performs:

`RegA = RegA - RegB`

### AND

`AND RegA RegB`

Performs a bitwise AND:

`RegA = RegA & RegB`

### OR

`OR RegA RegB`

Performs a bitwise OR:

`RegA = RegA | RegB`

### LOAD

`LOAD RegA RegB`

Loads a byte from memory:

`RegA = memory[RegB]`

The value stored in RegB is used as the memory address.

Example:

If `R0 = 100` and `memory[100] = 11`:

`LOAD R3 R0`

results in:

`R3 = 11`

### STORE

`STORE RegA RegB`

Stores a register value into memory:

`memory[RegB] = RegA`

The value stored in RegB is used as the memory address.

Example:

If `R2 = 11` and `R0 = 100`:

`STORE R2 R0`

results in:

`memory[100] = 11`

### JUMP

`JUMP RegA`

Sets the program counter to the value stored in RegA:

`PC = RegA`

Example:

If `R1 = 4`:

`JUMP R1`

causes the next instruction to be fetched from memory address 4.

## Memory

The CPU contains 256 bytes of memory, addressed from 0 to 255.

Program instructions and data share the same memory. Therefore, a STORE instruction can overwrite an instruction if it writes to a memory address containing program code.

For example, if an instruction is stored at memory address 2:

`STORE R2 R0`

with `R0 = 2` will overwrite that instruction with the value stored in R2.

## Program Execution

The CPU executes instructions using a fetch-decode-execute cycle:

1. Fetch the instruction at the current PC.
2. Increment the PC.
3. Decode the opcode and register fields.
4. Execute the instruction.
5. Repeat until HALT is executed.