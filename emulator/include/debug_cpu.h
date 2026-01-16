#pragma once 

#include "config.h"

void showMetrics(CPU*cpu){
    printf(ANSI_YELLOW"\nPROGRAM SIZE: \e[1;93m%d "ANSI_RESET,cpu->metrics.bytesInProgram);
    printf(ANSI_YELLOW"BYTES\nCOMPLETED \e[1;93m%d "ANSI_RESET, cpu->metrics.cycles);
    printf(ANSI_YELLOW"CYCLES IN \e[1;93m%f "ANSI_RESET,cpu->metrics.exetime); 
    printf(ANSI_YELLOW"SECONDS"ANSI_RESET);
}
void showFatalErrors(CPU*cpu){
    if (cpu->fatalError==NONE) {
        printf(ANSI_BOLD_GREEN"\nEXECUTED PROGRAM WITH ZERO ERRORS :]"ANSI_RESET);
        return;
    }

    printf(ANSI_BOLD_RED"\n\nPROGRAM EXITED WITH ERROR CODE %d"ANSI_RESET, cpu->fatalError);
    switch(cpu->fatalError) {
        case ERROR_LOADING_PROGRAM:              printf(ANSI_RED"\nERROR, LOADING PROGRAM"ANSI_RESET); break;
        case ERROR_FETCHING_INSTRUCTION:         printf(ANSI_RED"\nERROR, FETCHING INSTRUCTION %d"ANSI_RESET, cpu->programCounter); break;
        case ERROR_DECODING_INSTRUCTION:         printf(ANSI_RED"\nERROR, DECODING INSTRUCTOIN %d"ANSI_RESET, cpu->programCounter); break;
        case ERROR_EXECUTING_INTRUCTION:         printf(ANSI_RED"\nERROR, EXECUTING INSTRUCTION %d"ANSI_RESET, cpu->programCounter); break;
        case ERROR_MEMORY_OUT_OF_BOUNDS:         printf(ANSI_RED"\nERROR, PROGRAM ATTEPTE TO ACCESS MEMORY OUT OF BOUNDS"ANSI_RESET); break;
        case ERROR_INVALID_ARITHMETIC_OPERATION: printf(ANSI_RED"\nERROR, PROGRAM ATTEMPTED TO EXECUTE INVALID ARITHMETIC INSTRUCTION"ANSI_RESET); break;
        case ERROR_PROGRAM_SIZE:                 printf(ANSI_RED"\nERROR, PROGRAM SIZE TOO LARGE"ANSI_RESET);
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
        
        if( i<10 )  {
            printf(ANSI_BOLD_WHITE" R%d:   "ANSI_RESET,i); 
            printf("0x%02X",cpu->gpRegs[i]); 
        } else{
            printf(ANSI_BOLD_WHITE" R%d:  "ANSI_RESET,i); 
            printf("0x%02X",cpu->gpRegs[i]);
        }   
        if ((i+1) % 4 == 0) printf("\n"); // print in rows of 4
    }
    printf(ANSI_YELLOW"========================================="ANSI_RESET);
}
void inspectPC(CPU*cpu){
     printf(ANSI_BOLD_WHITE"\n   %d    "ANSI_RESET, cpu->metrics.cycles);
    printf("%d  \x1b[33m->\x1b[0m  ",cpu->programCounter); 
    printf("0x%02X     ",cpu->instructionReg[0]);
    for ( int i=1; i<4; i++) {
        if (cpu->instructionReg[0] == HALT) printf("0x00 ");
        else printf("0x%02X ",cpu->instructionReg[i]);
    }
}
void inspectFlags(CPU*cpu) {
    printf(ANSI_YELLOW"\n=====ZRO======OFW======NEG======ERR======"ANSI_RESET);
    printf("\n\x1b[33mFLAGS\x1b[0m %d        %d        %d        %d",cpu->zeroFlag,cpu->overflowFlag,cpu->negativeFlag,cpu->errorFlag);
    printf(ANSI_YELLOW"\n========================================="ANSI_RESET);
}
