#pragma once 

#include "config.h"

// RAM and ROM memory & program loading

// https://www.tutorialkart.com/c-programming/how-to-read-binary-data-from-a-file-in-c/

void clearRAM(CPU* cpu){ // clears data in ram but not read only memory
    for (int j=0; j<INST_LENGTH; j++){
        for (int i=RAM_SIZE/2; i<RAM_SIZE; i++){
            cpu->ram[i]=0;
        }
    }
}

void loadProgram(CPU *cpu){ // loads program from external txt file into 
    FILE *binFile = fopen("program.bin", "r");         // read only memory, first half of ram
    uint16_t programSize; 
    if (binFile == NULL){
        cpu->fatalError=ERROR_LOADING_PROGRAM;
        fclose(binFile);
        return;
    }
    
    size_t bytesInProgram = fread(&programSize,sizeof(uint16_t),1 ,binFile); // read size of program (first 2 bytes)
    if (!(bytesInProgram > RAM_SIZE/2)) {
        size_t readbytes = fread(cpu->ram, sizeof(int8_t),programSize,binFile); // load program into ram
        fclose(binFile);
        return;
    } 
    cpu->fatalError=ERROR_PROGRAM_SIZE;    
}

// for reference https://www.youtube.com/watch?v=Ui6QyzcD3_E