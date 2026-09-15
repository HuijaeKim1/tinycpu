#include <stdio.h>
#include <stdint.h>

int main(void){

    uint8_t registers[4] = {0, 0, 0, 0}; // Initialize registers R0-R3
    uint8_t memory[256] = {0}; // Initialize all 256 memory locations to 0
    
    uint8_t pc = 0; // Initalize PC

    memory[0] = 5;

    uint8_t running = 1;

    registers[1] = 4;
    registers[2] = 7;

    memory[0] = 0b00110010;    // ADD R2, R1
    memory[1] = 0b00000000;    // HALT

    while(running) {
        uint8_t instruction = memory[pc]; // Fetch instruction from memory at PC
        pc++; // Increment PC

        uint8_t opcode = instruction >> 5; // Extract opcode (upper 3 bits)
        uint8_t regA = (instruction >> 3) & 0b00000011; // Extract regA (next 2 bits)
        uint8_t regB = (instruction >> 1) & 0b00000011; // Extract reg B

        switch (opcode){

            case 0:
                running = 0; // HALT operation
                break;

            case 1:
                registers[regA] = registers[regA] + registers[regB]; // ADD operation
                break;

            case 2:
                registers[regA] = registers[regA] - registers[regB]; // SUB operation
                break;

            case 3:
                registers[regA] = registers[regA] & registers[regB]; // AND operation
                break;

            case 4:
                registers[regA] = registers[regA] | registers[regB]; // OR operation
                break;

            case 5:
                registers[regA] = memory[registers[regB]]; // LOAD operation
                break;

            case 6:
                memory[registers[regB]] = registers[regA]; // STORE operation
                break;
            
            case 7:
                pc = registers[regA]; // JUMP operation
                break;
        }
    }

    printf("R2 = %u\n", registers[2]);

    return 0;
}