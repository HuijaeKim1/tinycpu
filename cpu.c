#include <stdio.h>
#include <stdint.h>

// ALU
uint8_t alu(uint8_t operation, uint8_t a, uint8_t b)
{
    switch (operation) {

        case 1:     // ADD
            return a + b;

        case 2:     // SUB
            return a - b;

        case 3:     // AND
            return a & b;

        case 4:     // OR
            return a | b;

        default:
            return 0;
    }
}

uint8_t fetch (uint8_t memory[], uint8_t *pc)
{
    uint8_t instruction = memory[*pc];
    (*pc)++;
    return instruction;
}

void decode(uint8_t instruction, uint8_t *opcode, uint8_t *regA, uint8_t *regB)
{
    *opcode = instruction >> 5;
    *regA = (instruction >> 3) & 0b00000011;
    *regB = (instruction >> 1) & 0b00000011;
}

void execute(uint8_t opcode, uint8_t regA, uint8_t regB, uint8_t registers[], uint8_t memory[], uint8_t *pc, uint8_t *running){
    switch(opcode){
        case 0:   //HALT
            *running = 0;
            break;
        
        case 1:  // ADD
        case 2:  // SUB
        case 3:  // AND
        case 4:  // OR
            registers[regA] = alu(opcode, registers[regA], registers[regB]);
            break;
        
        case 5:  // LOAD
            registers[regA] = memory[registers[regB]];
            break;
        
        case 6:  // STORE
            memory[registers[regB]] = registers[regA];
            break;
        
        case 7:  // JUMP
            *pc = registers[regA];
            break;


    }
}




int main(int argc, char *argv[])
{
    if (argc != 2)       // make sure user entered one program file
    {
        printf("Usage: ./tinycpu program.bin\n");
        return 1;
    }

    

    // CPU components
    uint8_t registers[4] = {0, 0, 0, 0};   // R0-R3
    uint8_t memory[256] = {0};              // 256 bytes of memory
    uint8_t pc = 0;                         // Program counter
    uint8_t running = 1;                    // CPU running flag


    registers[0] = 100;
    registers[1] = 4;
    registers[2] = 7;
    registers[3] = 1;


    FILE *file = fopen(argv[1], "rb");

    if (!file)
    {
        printf("Error: could not open program file\n");
        return 1;
    }

    size_t bytesRead = fread(memory, 1, 256, file);
    fclose(file);

    printf("Loaded %zu bytes into memory\n", bytesRead);


    while (running) {

        uint8_t currentPC = pc;


        // FETCH
        uint8_t instruction = fetch(memory, &pc);


        // DECODE
        uint8_t opcode;
        uint8_t regA;
        uint8_t regB;

        decode(instruction, &opcode, &regA, &regB);

        printf("PC=%u  Instruction=0x%02X  ", currentPC, instruction);

        switch (opcode) {
            case 0:
                printf("HALT");
                break;

            case 1:
                printf("ADD R%u R%u", regA, regB);
                break;

            case 2:
                printf("SUB R%u R%u", regA, regB);
                break;

            case 3:
                printf("AND R%u R%u", regA, regB);
                break;

            case 4:
                printf("OR R%u R%u", regA, regB);
                break;

            case 5:
                printf("LOAD R%u R%u", regA, regB);
                break;

            case 6:
                printf("STORE R%u R%u", regA, regB);
                break;

            case 7:
                printf("JUMP R%u", regA);
                break;
            }

        printf("\n");

        // EXECUTE
        execute(opcode, regA, regB, registers, memory, &pc, &running);

        }

    

    printf("R0 = %u\n", registers[0]);
    printf("R1 = %u\n", registers[1]);
    printf("R2 = %u\n", registers[2]);
    printf("R3 = %u\n", registers[3]);

    return 0;

}
