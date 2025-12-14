#ifndef CPU_HEADER
#define CPU_HEADER

#include "config.h"
#include "ALU.h"
#include "memory.h"
#include "control_unit.h"

void initCPU(CPU *cpu){ 
    initMemory(cpu); 
    initCtrlUnit(cpu);
    loadProgram(cpu);
    cpu->isRunning = true;
    cpu->errorFlag = false;    
}

void runCPU(CPU *cpu){ // fetch decode execute
    static DecodedInst inst;

    cpuFetch(cpu,PRINT_PC);
    inst = cpuDecode(cpu);
    cpuExecute(&inst,cpu);        
}

void debugCPU(CPU *cpu){
    debugRAM(PRINT_RAM_MODE,cpu);

    printf("Zero: %d ",cpu->zeroFlag); 
    printf("\nAbv:  %d ",(!cpu->negativeFlag&&!cpu->zeroFlag)); 
    printf("\nNeg:  %d ",cpu->negativeFlag); 
    printf("\nOvf:  %d ",cpu->overflowFlag); 
    printf("\nError:  %d ",cpu->errorFlag); 
    printf("\nReg 1:  %d ",cpu->gpRegs[1]); 
}


#endif