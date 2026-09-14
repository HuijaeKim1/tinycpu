# Tiny CPU ISA

## CPU Specifications

- 8-bit CPU
- 4 general-purpose registers: R0-R3
- 256 bytes of memory
- 8-bit program counter
- 8-bit instructions

## Opcodes

| Binary | Instruction |
|--------|-------------|
| 000 | HALT |
| 001 | ADD |
| 010 | SUB |
| 011 | AND |
| 100 | OR |
| 101 | LOAD |
| 110 | STORE |
| 111 | JUMP |

## Register Encoding

| Binary | Register |
|--------|----------|
| 00 | R0 |
| 01 | R1 |
| 10 | R2 |
| 11 | R3 |

## Arithmetic Instruction Format

8-bit instruction:

`[ opcode (3 bits) ][ Reg A (2 bits) ][ Reg B (2 bits) ][ unused (1 bit) ]`

For arithmetic/logic instructions:

`OP RegA, RegB` means:

`RegA = RegA OP RegB`

Example:

`ADD R2, R1`

encodes as:

`001 10 01 0` → `00110010`