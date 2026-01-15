#pragma once 

#include "config.h"
#include "ALU.h"
#include "memory.h"
#include "control_unit.h"

// DEBUGGING STUFF _____________________________________________________________________________
void showFatalErrors(CPU*cpu){
    if (cpu->fatalerror==NONE) {
        printf(ANSI_GREEN"\nFINISHED PROGRAM WITH ZERO ERRORS :]\n\n"ANSI_RESET);
        return;
    }

    printf(ANSI_RED"\n\nPROGRAM EXITED WITH ERROR CODE %d"ANSI_RESET, cpu->fatalerror);
    switch(cpu->fatalerror) {
        case ERROR_LOADING_PROGRAM:              printf(ANSI_RED"\nERROR, LOADING PROGRAM"ANSI_RESET); break;
        case ERROR_FETCHING_INSTRUCTION:         printf(ANSI_RED"\nERROR, FETCHING INSTRUCTION %d"ANSI_RESET, cpu->programCounter); break;
        case ERROR_DECODING_INSTRUCTION:         printf(ANSI_RED"\nERROR, DECODING INSTRUCTOIN %d"ANSI_RESET, cpu->programCounter); break;
        case ERROR_EXECUTING_INTRUCTION:         printf(ANSI_RED"\nERROR, EXECUTING INSTRUCTION %d"ANSI_RESET, cpu->programCounter); break;
        case ERROR_MEMORY_OUT_OF_BOUNDS:         printf(ANSI_RED"\nERROR, PROGRAM ATTEPTE TO ACCESS MEMORY OUT OF BOUNDS"ANSI_RESET); break;
        case ERROR_INVALID_ARITHMETIC_OPERATION: printf(ANSI_RED"\nERROR, PROGRAM ATTEMPTED TO EXECUTE INVALID ARITHMETIC INSTRUCTION"ANSI_RESET); break;
        default:                                 printf(ANSI_RED"\nUNKNOWN FATAL ERROR OCCURED"ANSI_RESET);return;
    }

}

void inspectRam(CPU*cpu){
    printf(ANSI_YELLOW"\n=================CPU RAM=================\n"ANSI_RESET);
    for (int i=0; i<RAM_SIZE; i++) {
        if ((i+1)%8 == 0) printf("\n"); // print in rows of 8 bytes
        printf(" 0x%02X",cpu->ram[i]);
    }
    printf(ANSI_YELLOW"\n========================================="ANSI_RESET);
}
void inspectRegisters(CPU*cpu){
    printf(ANSI_YELLOW"\n================REGISTERS================\n"ANSI_RESET);
    for (int i=0; i<CPU_REG_NO; i++) {
        if ((i+1) % 4 == 0) printf("\n"); // print in rows of 4
        if( i<10 ) printf(" R%d:  0x%02X",i,cpu->gpRegs[i]);
        else       printf(" R%d: 0x%02X",i,cpu->gpRegs[i]); 
    }
    printf(ANSI_YELLOW"\n========================================="ANSI_RESET);
}
void inspectPC(CPU*cpu){
    // printf(ANSI_YELLOW"\n==PC=====OPCODE==========OPERANDS========"ANSI_RESET);
    printf("\n  %d   ->  ",cpu->programCounter); 
    printf("0x%02X        ",cpu->instructionReg[0]);
    for ( int i=1; i<4; i++) {
        if (cpu->instructionReg[0] == HALT) printf("0x00 ");
        else printf("0x%02X ",cpu->instructionReg[i]);
    }
    // printf(ANSI_YELLOW"\n========================================="ANSI_RESET);
}

// RUNNING CPU ___________________________________________________________________
void initCPU(CPU*cpu) {
    if (SHOW_PC) printf(ANSI_YELLOW"\n==PC=====OPCODE==========OPERANDS========"ANSI_RESET);
    initCtrlUnit(cpu);
    loadProgram(cpu);
}
void runCPU(CPU*cpu) {
    cpuFetch(cpu); 
    cpuDecodeExecute(cpu);
    if (SHOW_PC) inspectPC(cpu);
}