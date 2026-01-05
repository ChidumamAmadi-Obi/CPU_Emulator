#ifndef CPU_MEM
#define CPU_MEM

#include "config.h"

// RAM and ROM memory & program loading

void clearRAM(CPU* cpu){ // clears data in ram but not read only memory
    for (int j=0; j<INST_LENGTH; j++){
        for (int i=RAM_SIZE/2; i<RAM_SIZE; i++){
            cpu->ram[i][j]=0;
        }
    }
}

void loadProgram(CPU *cpu){                         // loads program from external txt file into 
    FILE *fptr = fopen("program.asm", "r");         // read only memory, first half of ram
    if (fptr == NULL){
        printf("ERROR OPENING PROGRAM FILE\n");
        return;
    }

    int ch;
    int instruction=0;
    int letter=0;
    bool delComment=false; 
    bool hasData=false; 
    bool newLine=false;

    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') { 
            if (hasData) instruction++; // only inc if line has data
            letter = 0;
            delComment = false;  // Reset comment flag for next line
            hasData=false;
            newLine=true;
        } else if (ch == ASCII_SPACE && newLine) { // trim whitespace
        } else {
            if (ch == ASCII_SEMI_COLON){
                if (!delComment) { // deletes both inline and whole line comments
                    cpu->ram[instruction][letter]=ch; //leaves semicolon
                    letter++;
                }
                delComment = true; // Skip line if it starts with ';'
                newLine=false;
            } else if (!delComment) {
                if (letter < INST_LENGTH - 1) {
                    hasData=true;
                    newLine=false;
                    cpu->ram[instruction][letter] = ch; // load to ram as normal
                    letter++;
                }
            }
        }
    }
    fclose(fptr);
}

void debugRAM(MemPrintModes mode, CPU *cpu){ // prints contents of RAM
    uint8_t mem;
    if (mode!=NONE) {
        for (int x=0; x<RAM_SIZE; x++){
            printf("%d ->   ", x); // prints address of instruction
            for (int y=0; y<INST_LENGTH; y++){
                mem = cpu->ram[x][y]; 
                if (mem == 0) {// do nothing
                } else {
                    switch(mode) {
                        case CHAR:      printf("%c",mem); break;
                        case INTEGER:   printf("%d ",mem); break;
                        case HEX:       printf("0x%x ",mem); break;
                        default:        printf("%c",mem); break;
                    }
                }
            }
            printf("\n");
        }        
    }
}

// for reference https://www.youtube.com/watch?v=Ui6QyzcD3_E

#endif