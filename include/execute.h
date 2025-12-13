#ifndef CPU_EXECUTE
#define CPU_EXECUTE

#include "config.h"
#include "ALU.h"
#include "memory.h"

void loadInst(){ // take thing from ram and store in a genreg

}

void storeInst(){ //take thing from gerreg and store in ram

}

void arithmeticInst(DecodedInst *inst, CPU *cpu){ // can only do arithmetic without memory right now
    ALUResults alu = {0};
    
    int8_t inputA = atoi(inst->operand1);
    int8_t inputB = atoi(inst->operand2);

    switch(inst->opcodeNo){
        case ADD: alu = ALUEmulator(inputA,inputB,OP_ADD); break;
        case SUB: alu = ALUEmulator(inputA,inputB,OP_SUB); break;
        case AND: alu = ALUEmulator(inputA,inputB,OP_AND); break;
        case OR: alu = ALUEmulator(inputA,inputB,OP_OR); break;
        case XOR: alu = ALUEmulator(inputA,inputB,OP_XOR); break;
        case EQU: alu = ALUEmulator(inputA,inputB,OP_EQU); break;
        default: break;
    }
    cpu->gpRegs[0] = alu.output;
}

#endif