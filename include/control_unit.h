#ifndef CPU_CTRL_UNIT
#define CPU_CTRL_UNIT

#include "config.h"
#include "ALU.h"
#include "memory.h"
#include "execute.h"

void initCtrlUnit(CPU *cpu){ // initializes cpu registers on start up
    cpu->programCounter=0;
    for (int i=0; i<INST_LENGTH; i++){
        cpu->gpRegs[i]=0;
        cpu->instructionReg[i]=0;
    }
}

void cpuFetch(CPU *cpu){ // fetches next instruction in memory and stores it into the inst reg
    for (int i=0; i<INST_LENGTH; i++){
        cpu->instructionReg[i] = cpu->ram[cpu->programCounter][i];
        printf("0x%x ",cpu->instructionReg[i]);
    }
    printf("\n");
}

CPUInstruction extractOpcode(DecodedInst *inst){
    if ( strcmp(inst->opcode,"HALT") == 0) return HALT;
    else if ( strcmp(inst->opcode,"STR") == 0) return STR;
    else if ( strcmp(inst->opcode,"LD") == 0) return LD;
    else if ( strcmp(inst->opcode,"JMP") == 0) return JMP;
    else if ( strcmp(inst->opcode,"JMP_OFW") == 0) return JMP_OFW;
    else if ( strcmp(inst->opcode,"JMP_ZRO") == 0) return JMP_ZRO;
    else if ( strcmp(inst->opcode,"JMP_NEG") == 0) return JMP_NEG;
    else if ( strcmp(inst->opcode,"JMP_ABV") == 0) return JMP_ABV;

    else if ( strcmp(inst->opcode,"ADD") == 0) return ADD; // arithmetic ops
    else if ( strcmp(inst->opcode,"SUB") == 0) return SUB;
    else if ( strcmp(inst->opcode,"OR") == 0) return OR;
    else if ( strcmp(inst->opcode,"XOR") == 0) return XOR;
    else if ( strcmp(inst->opcode,"EQU") == 0) return EQU;

    else return 0; // invalid opcode
}

DecodedInst cpuDecode(CPU *cpu) {
    uint8_t *instPtr = cpu->instructionReg;
    static char instString[INST_LENGTH];
    DecodedInst decodedInst = {0}; // clear inst reg

    if (*instPtr != '\n') {
        for (int i=0; *instPtr != ASCII_SEMI_COLON; i++) { // converts instruction into string to be parsed
            instString[i] = *instPtr;
            instPtr++;
            if (*instPtr == ASCII_SEMI_COLON) instString[i+1] = '\0';
        }  
        decodedInst.opcode = strtok(instString, " "); // parse instruction
        decodedInst.operand1 = strtok(NULL, " ");
        decodedInst.operand2 = strtok(NULL, " ");
        decodedInst.operand3 = strtok(NULL, " ");
    }
    decodedInst.opcodeNo = extractOpcode(&decodedInst);
    return decodedInst;
}

void cpuExecute(DecodedInst *inst, CPU *cpu){
    switch(inst->opcodeNo){
        case ADD: case SUB: case AND: case OR: case XOR: case EQU: //math ops
            arithmeticInst(inst,cpu); 
            break;

        case STR: storeInst(inst,cpu); break; // address ops
        case LD: break;
        case JMP: break;
        case HALT: cpu->isRunning = false; break; // end program
        case JMP_ABV: break;
        case JMP_NEG: break;
        case JMP_OFW: break;
        case JMP_ZRO: break;
        default: break;
    }
    cpu->programCounter++; // incriment pc to move to the next instruction
}

#endif