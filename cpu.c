#include <stdio.h>
#include <stdint.h>

int main(void){

    uint8_t registers[4] = {0, 0, 0, 0}; // Initialize registers R0-R3
    uint8_t memory[256] = {0}; // Initialize all 256 memory locations to 0
    
    uint8_t pc = 0; // Initalize PC

    memory[0] = 5;

    uint8_t running = 1;

    while(running) {
        uint8_t instruction = memory[pc]; // Fetch instruction from memory at PC
        pc++; // Increment PC

        uint8_t opcode = instruction >> 5; // Extract opcode (upper 3 bits)

    
    

    return 0;
    }
}