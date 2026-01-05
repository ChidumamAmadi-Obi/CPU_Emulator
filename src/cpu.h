#ifndef CPU_HEADER
#define CPU_HEADER

#include "config.h"
#include "ALU.h"
#include "memory.h"
#include "control_unit.h"

void printInst(CPU *cpu){
    for (int i=0; i<INST_LENGTH; i++){
        if ((cpu->instructionReg[i] != 0) && (cpu->instructionReg[i] != ASCII_SEMI_COLON)) { // print if needed
            printf("%c",cpu->instructionReg[i]);
        } 
    }
    printf("\n");
}

void visualizeSteps(CPU *cpu){
    printf("___________________________________\n");
    printf("   PROGRAM COUNTER    |  %d\n",cpu->programCounter); 
    printf(" INSTRUCTION REGISTER |  "); printInst(cpu);
    printf("      ZERO FLAG       |  %d\n",cpu->zeroFlag);
    printf("    OVERFLOW FLAG     |  %d\n",cpu->overflowFlag);
    printf("    NEGATIVE FLAG     |  %d\n",cpu->negativeFlag);
    printf("     ERROR FLAG       |  %d\n",cpu->errorFlag);
    printf("___________________________________\n");
    printf("R0  | %d\nR1  | %d\nR2  | %d\nR3  | %d\nR4  | %d\nR5  | %d\nR6  | %d\nR7  | %d\nR8  | %d\nR9  | %d\nR10 | %d\nR11 | %d\nR12 | %d\nR13 | %d\nR14 | %d\nR15 | %d\n",
    cpu->gpRegs[0],cpu->gpRegs[1],cpu->gpRegs[2],cpu->gpRegs[3],cpu->gpRegs[4],cpu->gpRegs[5],cpu->gpRegs[6],cpu->gpRegs[7],
    cpu->gpRegs[8],cpu->gpRegs[9],cpu->gpRegs[10],cpu->gpRegs[11],cpu->gpRegs[12],cpu->gpRegs[13],cpu->gpRegs[14],cpu->gpRegs[15]);
    printf("___________________________________\n");
}

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
    visualizeSteps(cpu);
    cpu->metrics.cycles++; // counts each cycle        
}

void debugRegisters(CPU*cpu){
    for (int i=0; i<CPU_REG_NO; i++){
        printf("\nREG %d -> %d",i,cpu->gpRegs[i]);
    }
}

void debugCPU(CPU *cpu){
    debugRAM(PRINT_RAM_MODE,cpu);
    // more debugging here......
}

#endif