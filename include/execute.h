#ifndef CPU_EXECUTE
#define CPU_EXECUTE

#include "config.h"
#include "ALU.h"
#include "memory.h"

int getRegNo(char*operand){ // extracts number from operand
    if(operand[0] =='r'){
        char*regNo = strtok(operand,"r");
        return atoi(regNo);
    } else return atoi(operand);
    return 0;
}

int getMemLocation(char*operand) {
    bool ifMemLocation = (operand[0] == 'm') && (operand[1] == 'm') && (operand[1] == 'm');
    return 0;
}

void loadInst(){ // take thing from ram and store in reg

}

void storeInst(DecodedInst *inst, CPU *cpu){ // take thing from reg and store in ram
    // operand 1 destination eg mem1
    // operand 2 val eg r1

    static uint8_t destination; 
    static uint8_t location;

    if (inst->operand1[0] =='r'){ // if both r registers
        char*regNo = strtok(inst->operand1,"r");
        destination = cpu->gpRegs[atoi(regNo)];
    }
    if (inst->operand2[0] =='r'){ 
        char*regNo = strtok(inst->operand2,"r");
        location = cpu->gpRegs[atoi(regNo)];
    } else location = atoi(inst->operand2);

    cpu->gpRegs[destination]=cpu->gpRegs[location];
    // printf("%d %d",cpu->gpRegs[destination],cpu->gpRegs[location]);
}

void arithmeticInst(DecodedInst *inst, CPU *cpu){ 
    ALUResults alu = {0};
    int8_t inputA;
    int8_t inputB;
    int regOut = getRegNo(inst->operand1);

    if (inst->operand3[0] =='r'){ 
        char*regNo = strtok(inst->operand3,"r");
        inputB = cpu->gpRegs[atoi(regNo)];
    } else inputB = atoi(inst->operand3);

    if (inst->operand2[0] =='r'){ 
        char*regNo = strtok(inst->operand2,"r");
        inputA = cpu->gpRegs[atoi(regNo)];
    } else inputA = atoi(inst->operand2);

    switch(inst->opcodeNo){
        case ADD: alu = ALUEmulator(inputA,inputB,OP_ADD); break;
        case SUB: alu = ALUEmulator(inputA,inputB,OP_SUB); break;
        case AND: alu = ALUEmulator(inputA,inputB,OP_AND); break;
        case OR: alu = ALUEmulator(inputA,inputB,OP_OR); break;
        case XOR: alu = ALUEmulator(inputA,inputB,OP_XOR); break;
        case EQU: alu = ALUEmulator(inputA,inputB,OP_EQU); break;
        default: break;
    }
    cpu->gpRegs[regOut] = alu.output;
}

#endif