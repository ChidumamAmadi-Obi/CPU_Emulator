#ifndef CPU_REGISTERS
#define CPU_REGISTERS

#include "config.h"

void CPUinit(){
    cpu.instructionReg = 0;
    cpu.programCounter = &memory.rom[0]; // points to start of read only memory
    for(int i = 0; i < 16; i++) { // Initialize all registers
        cpu.gpRegs[i] = 0;  
    }
}

void incPC(){ // increments program counter
    cpu.programCounter++; // moves to next memory location
}

uint8_t fetchInst(){ // gets next instruction and then increments pc
    uint8_t instruction = *(cpu.programCounter);
    incPC();
    return instruction;
}

#endif