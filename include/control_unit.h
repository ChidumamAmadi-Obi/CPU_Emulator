#ifndef CPU_CTRL_UNIT
#define CPU_CTRL_UNIT

#include "config.h"
#include "ALU.h"
#include "memory.h"
#include "execute.h"

void initCtrlUnit(CPU *cpu){
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

void extractOpcode(DecodedInst *inst){
    if ( strcmp(inst->opcode,"HALT") == 0) inst->opcodeNo = HALT;
    else if ( strcmp(inst->opcode,"STR") == 0) inst->opcodeNo = STR;
    else if ( strcmp(inst->opcode,"LD") == 0) inst->opcodeNo = LD;
    else if ( strcmp(inst->opcode,"JMP") == 0) inst->opcodeNo = JMP;
    else if ( strcmp(inst->opcode,"JMP_OFW") == 0) inst->opcodeNo = JMP_OFW;
    else if ( strcmp(inst->opcode,"JMP_ZRO") == 0) inst->opcodeNo = JMP_ZRO;
    else if ( strcmp(inst->opcode,"JMP_NEG") == 0) inst->opcodeNo = JMP_NEG;
    else if ( strcmp(inst->opcode,"JMP_ABV") == 0) inst->opcodeNo = JMP_ABV;

    else if ( strcmp(inst->opcode,"ADD") == 0) inst->opcodeNo = ADD; // arithmetic ops
    else if ( strcmp(inst->opcode,"SUB") == 0) inst->opcodeNo = SUB;
    else if ( strcmp(inst->opcode,"OR") == 0) inst->opcodeNo = OR;
    else if ( strcmp(inst->opcode,"XOR") == 0) inst->opcodeNo = XOR;
    else if ( strcmp(inst->opcode,"EQU") == 0) inst->opcodeNo = EQU;

    else inst->opcodeNo = 0; // invalid opcode
}

DecodedInst cpuDecode(CPU *cpu) {
    uint8_t *instPtr = cpu->instructionReg;
    static char instString[INST_LENGTH];
    DecodedInst decodedInst = {0}; // clear inst reg

    if (*instPtr != 0) {
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
    extractOpcode(&decodedInst);
    return decodedInst;
}

void cpuExecute(DecodedInst *inst, CPU *cpu){
    switch(inst->opcodeNo){
        case ADD: case SUB: case AND: case OR: case XOR: case EQU: 
        arithmeticInst(inst,cpu); 
        break;

        case STR: break;
        case LD: break;
        case JMP: break;
        case HALT: break;
        case JMP_ABV: break;
        case JMP_NEG: break;
        case JMP_OFW: break;
        case JMP_ZRO: break;
        default: break;
    }
    arithmeticInst(inst,cpu);
}

#endif