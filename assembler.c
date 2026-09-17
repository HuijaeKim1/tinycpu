#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: ./assembler input.asm output.bin\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "wb");

    if (!input || !output) {
        printf("Error opening files.\n");
        return 1;
    }

    char line[100];

    while (fgets(line, sizeof(line), input)) {

        char operation[10];
        int regA, regB;

        int count = sscanf(line, "%9s R%d R%d",
                           operation, &regA, &regB);

        uint8_t opcode;

        if (strcmp(operation, "HALT") == 0) {
            opcode = 0;
        }
        else if (strcmp(operation, "ADD") == 0) {
            opcode = 1;
        }
        else if (strcmp(operation, "SUB") == 0) {
            opcode = 2;
        }
        else if (strcmp(operation, "AND") == 0) {
            opcode = 3;
        }
        else if (strcmp(operation, "OR") == 0) {
            opcode = 4;
        }
        else if (strcmp(operation, "LOAD") == 0) {
            opcode = 5;
        }
        else if (strcmp(operation, "STORE") == 0) {
            opcode = 6;
        }
        else if (strcmp(operation, "JUMP") == 0) {
            opcode = 7;
        }
        else {
            printf("Unknown operation: %s\n", operation);
            continue;
        }

        // Check that the correct number of registers were given
        if (opcode == 0 && count != 1) {
            printf("HALT does not take any registers.\n");
            continue;
        }
        else if (opcode == 7 && count != 2) {
            printf("Invalid JUMP instruction.\n");
            continue;
        }
        else if (opcode != 0 && opcode != 7 && count != 3) {
            printf("Invalid %s instruction.\n", operation);
            continue;
        }

        // Check register numbers
        if (opcode == 7) {
            // JUMP only uses regA
            if (regA < 0 || regA > 3) {
                printf("Invalid register\n");
                continue;
            }
        }
        else if (opcode != 0) {
            // All instructions except HALT and JUMP use two registers
            if (regA < 0 || regA > 3 ||
                regB < 0 || regB > 3) {
                printf("Invalid register\n");
                continue;
            }
        }

        // Construct the 8-bit machine instruction
        uint8_t instruction;

        if (opcode == 0) {
            instruction = 0;
        }
        else if (opcode == 7) {
            instruction = (opcode << 5) | (regA << 3);
        }
        else {
            instruction = (opcode << 5)
                        | (regA << 3)
                        | (regB << 1);
        }

        // Write the instruction to the binary file
        fwrite(&instruction, 1, 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}