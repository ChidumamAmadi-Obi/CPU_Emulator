#ifndef CPU_HEADER
#define CPU_HEADER

#include "config.h"
#include "ALU.h"
#include "memory.h"
#include "control_unit.h"

static DecodedInst inst;

void initCPU(CPU *cpu){
    initMemory(cpu); 
    initCtrlUnit(cpu);
    loadProgram(cpu);
    cpu->isRunning = true;
}

void runCPU(CPU *cpu){
    cpuFetch(cpu);
    inst = cpuDecode(cpu);
    cpuExecute(&inst,cpu);        
}


#endif