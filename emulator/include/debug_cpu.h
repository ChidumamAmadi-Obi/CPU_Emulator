#pragma once 

#include "config.h"
#include <terminal_colors.h>

void showMetrics(CPU*cpu){
    COLOR_YELLOW; printf("\nPROGRAM SIZE: "); COLOR_RESET;               COLOR_BOLD_YELLOW; printf("%ld",cpu->metrics.bytesInProgram); COLOR_RESET;
    COLOR_YELLOW; printf("/%d BYTES\nCOMPLETED ",ROM_SIZE); COLOR_RESET; COLOR_BOLD_YELLOW; printf("%d ", cpu->metrics.cycles); COLOR_RESET;
    COLOR_YELLOW; printf("CYCLES IN "); COLOR_RESET;                     COLOR_BOLD_YELLOW; printf("%f ",cpu->metrics.exetime); COLOR_RESET;
    COLOR_YELLOW; printf("SECONDS"); COLOR_RESET;
}
void showFatalErrors(CPU*cpu){
    if (cpu->fatalError==NONE) {
        COLOR_BOLD_GREEN; printf("\nEXECUTED PROGRAM WITH ZERO ERRORS :]\n"); COLOR_RESET;
        return;
    }

    COLOR_BOLD_RED; printf("\n\nPROGRAM EXITED WITH ERROR CODE %d", cpu->fatalError);
    switch(cpu->fatalError) {
        case ERROR_LOADING_PROGRAM:             COLOR_RED; printf("\nUNABLE TO LOAD PROGRAM"); break;
        case ERROR_FETCHING_INSTRUCTION:        COLOR_RED; printf("\nUNABLE TO FETCH INSTRUCTION PC: %d", cpu->programCounter);break;
        case ERROR_DECODING_INSTRUCTION:        COLOR_RED; printf("\nUNABLE TO DECODE INSTRUCTION PC: %d", cpu->programCounter); break;
        case ERROR_EXECUTING_INTRUCTION:        COLOR_RED; printf("\nUNABLE TO EXECUTE INSTRUCTION PC: %d", cpu->programCounter);break;
        case ERROR_MEMORY_OUT_OF_BOUNDS:        COLOR_RED; printf("\nPROGRAM ATTEMPTED TO ACCESS MEMORY OUT OF BOUNDS, PC: %d",cpu->programCounter); break;
        case ERROR_INVALID_ARITHMETIC_OPERATION:COLOR_RED; printf("\nPROGRAM ATTEMPTED TO EXECUTE INVALID ARITHMETIC INSTRUCTION"); break;
        case ERROR_PROGRAM_SIZE:                COLOR_RED; printf("\nPROGRAM SIZE TOO LARGE"); break;
        default:                                COLOR_BOLD_RED; printf("\nUNKNOWN FATAL ERROR OCCURED"); break;
    } COLOR_RESET;
}
void inspectRam(CPU*cpu){
   COLOR_YELLOW; printf("\n=================CPU RAM=================\n"); COLOR_RESET;
    for (int i=0; i<RAM_SIZE; i++) {
        if ((i+1)%8 == 0) printf("\n"); // print in rows of 8 bytes
        printf(" 0x%02X",cpu->ram[i]);
    }
   COLOR_YELLOW; printf("\n========================================="); COLOR_RESET;
}
void inspectRegisters(CPU*cpu){
   COLOR_YELLOW; printf("\n================REGISTERS================\n"); COLOR_RESET;
    for (int i=0; i<CPU_REG_NO; i++) {
        
        if( i<10 )  {
            COLOR_BOLD_WHITE; printf(" R%d:   ",i); COLOR_RESET;
            printf("0x%02X",cpu->gpRegs[i]); 
        } else{
            COLOR_BOLD_WHITE; printf(" R%d:  ",i); COLOR_RESET;
            printf("0x%02X",cpu->gpRegs[i]);
        }   
        if ((i+1) % 4 == 0) printf("\n"); // print in rows of 4
    }
    COLOR_YELLOW; printf("========================================="); COLOR_RESET;
}
void inspectPC(CPU*cpu){
    COLOR_BOLD_WHITE; printf("\n   %d    ", cpu->metrics.cycles); COLOR_RESET;
    printf("%d  \x1b[33m->\x1b[0m  ",cpu->programCounter); 
    printf("0x%02X     ",cpu->instructionReg[0]);
    for ( int i=1; i<4; i++) {
        if (cpu->instructionReg[0] == HALT) printf("0x00 ");
        else printf("0x%02X ",cpu->instructionReg[i]);
    }
}
void inspectFlags(CPU*cpu) {
    COLOR_YELLOW; printf("\n=====ZRO======OFW======NEG======ERR======"); COLOR_RESET;
    printf("\n\x1b[33mFLAGS\x1b[0m %d        %d        %d        %d",cpu->zeroFlag,cpu->overflowFlag,cpu->negativeFlag,cpu->errorFlag);
    COLOR_YELLOW; printf("\n========================================="); COLOR_RESET;
}
