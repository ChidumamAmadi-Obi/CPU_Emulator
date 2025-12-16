#ifndef CPU_HEADER
#define CPU_HEADER

#include "config.h"
#include "ALU.h"
#include "memory.h"
#include "control_unit.h"

void initCPU(CPU *cpu){ // on startup...
    loadProgram(cpu);
    cpu->isRunning = true;
}

void resetCPU(CPU *cpu){ // (in progress) on key press cpu will be reset...
    clearRAM(cpu);
    initCtrlUnit(cpu);
}

void runCPU(CPU *cpu){ // fetch decode execute
    static DecodedInst inst;

    cpuFetch(cpu,PRINT_PC);
    inst = cpuDecode(cpu);
    cpuExecute(&inst,cpu);
    cpu->metrics.cycles++; // counts each cycle        
}

void debugRegisters(CPU*cpu){
    for (int i=0; i<CPU_REG_NO; i++){
        printf("\nREG %d: %d",i,cpu->gpRegs[i]);
    }
}

void debugCPU(CPU *cpu){
    debugRAM(PRINT_RAM_MODE,cpu);
    // more debugging here......
}

#endif