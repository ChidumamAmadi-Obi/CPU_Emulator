#pragma once 

#include "config.h"

// RAM and ROM memory & program loading

void clearRAM(CPU* cpu){ // clears data in ram but not read only memory
    for (int j=0; j<INST_LENGTH; j++){
        for (int i=RAM_SIZE/2; i<RAM_SIZE; i++){
            cpu->ram[i]=0;
        }
    }
}

void loadProgram(CPU *cpu){ // loads program from external txt file into read only memory
    FILE *binFile = fopen("program.bin", "rb");        
    uint32_t programSize; 
    size_t bytesRead=0;
    if (binFile == NULL){
        cpu->fatalError=ERROR_LOADING_PROGRAM;
        return;
    }
    
    fread(&programSize,sizeof(uint16_t),1 ,binFile); // read size of program (first 2 bytes)
    bytesRead = fread(cpu->ram, sizeof(uint8_t),programSize,binFile); // read rest of bytes and load into ram 
    if (!(bytesRead > ROM_SIZE)) {
        cpu->metrics.bytesInProgram=bytesRead;
        fclose(binFile);
        return;
    } 
    cpu->fatalError=ERROR_PROGRAM_SIZE;    
    fclose(binFile);
}

/* for reference 
https://www.youtube.com/watch?v=Ui6QyzcD3_E
https://www.tutorialkart.com/c-programming/how-to-read-binary-data-from-a-file-in-c/
*/
