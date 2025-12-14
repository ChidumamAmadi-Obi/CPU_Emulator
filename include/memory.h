#ifndef CPU_MEM
#define CPU_MEM

#include "config.h"

void initMemory(CPU *cpu){
    for (int j=0; j<INST_LENGTH; j++){
        for (int i=0; i<RAM_SIZE; i++){
            cpu->ram[i][j]=0;
        }
    }
}

void loadProgram(CPU *cpu){ // loads program into read only memory, first half of ram
    FILE *fptr = fopen("program.txt", "r");
    if (fptr == NULL){
        printf("Error opening program file\n");
        return;
    }

    int ch;
    int instruction=0;
    int letter=0;

    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n'){
            instruction++;
            letter=0;
        } else {
            cpu->ram[instruction][letter] = ch;
            letter++;
        }
    }
    fclose(fptr);
}

void debugRAM(MemPrintModes mode, CPU *cpu){ // prints contents of RAM
    uint8_t mem;
    for (int x=0; x<RAM_SIZE; x++){
        printf("%d   ", x); // prints address of instruction
        for (int y=0; y<INST_LENGTH; y++){
            mem = cpu->ram[x][y]; // program is loaded into first half of memory (adress 0-32)
            if (mem == 0) printf("_ ");
            else {
                switch(mode) {
                    case CHAR:      printf("%c",mem); break;
                    case INTEGER:   printf("%d ",mem); break;
                    case HEX:       printf("0x%x ",mem); break;
                    default:        printf("%c",mem); break;
                }
                
            }
        }
        printf("\n\n");
    }
}

// reference https://www.youtube.com/watch?v=Ui6QyzcD3_E

#endif