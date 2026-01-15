#pragma once
// Control Unit

#include "config.h"
#include "ALU.h"
#include "memory.h"
#include "execute.h"

uint8_t numberOfArgs(CPU*cpu, uint8_t opcode){ // return amount of operands in instruction
    switch(opcode) { 
        case STR: case LD: case LI: case MOV:
            return 2; 

        case JMP: case JMP_ABV: case JMP_NEG: case JMP_OFW: case JMP_ZRO:
            return 1; 

        case ADD: case SUB: case MUL: case AND: case OR: case XOR: case EQU: case DIV:
        case ADDI: case SUBI: case MULI: case ANDI: case ORI: case XORI: case EQUI: case DIVI:
            return 3;
        
        case HALT: return 0;  
        default: 
            cpu->fatalerror=ERROR_FETCHING_INSTRUCTION; // if first instruction is not a recognized opcode send error
            return 0;
    }
}

void initCtrlUnit(CPU *cpu){ // initializes cpu registers on start up
    cpu->fatalerror=NONE;
    cpu->errorFlag=0; // clear all flags and regs
    cpu->zeroFlag=0;
    cpu->overflowFlag=0;
    cpu->negativeFlag=0;
    cpu->programCounter=0;
    cpu->ramPtr=0;

    cpu->isJumping=false;
    cpu->isRunning=true;

    for (int i=0; i<INST_LENGTH; i++){ cpu->instructionReg[i]=0;}
    for (int i=0; i<CPU_REG_NO; i++) { cpu->gpRegs[i]=0;  }
}

// _______________________________________________________________________________
void cpuFetch(CPU *cpu) {
    uint8_t operands = numberOfArgs(cpu,cpu->ram[cpu->ramPtr]); // calu number of operands to read
    for (int i=0 ; i<=operands; i++) { 
        cpu->instructionReg[i] = cpu->ram[cpu->ramPtr];
        cpu->ramPtr++;
    }        
}
void cpuDecodeExecute(CPU *cpu){
    switch(cpu->instructionReg[0]) {
        case ADD: case SUB: case MUL: case AND: case OR: case XOR: case EQU: case DIV:
        case ADDI: case SUBI: case MULI: case ANDI: case ORI: case XORI: case EQUI: case DIVI:
            arithmeticInst(cpu);
            break;

        case JMP_ABV: case JMP_NEG: case JMP_OFW: case JMP_ZRO:
            // jumpCondInst(cpu);
            break;
        case JMP: // jumpInst(); 
            break;

        case STR:  storeInst(cpu); break;
        case LD:   loadInst(cpu); break;
        case LI:   loadImmInst(cpu); break;
        case MOV:  movInst(cpu); break;
        case HALT: cpu->isRunning = false; break; // end program  

        default: 
            cpu->fatalerror=ERROR_DECODING_INSTRUCTION; // if first instruction is not an opcode send error
            return;
    }
    if (cpu->isJumping) cpu->isJumping = false;
    else cpu->programCounter++;
    cpu->metrics.executedInstructions++;
}