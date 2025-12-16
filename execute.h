#ifndef CPU_EXECUTE
#define CPU_EXECUTE

// CPU instructions

#include "config.h"
#include "ALU.h"
#include "memory.h"

int8_t getRegNo(char*operand){ // extracts reg number from operand
    if(operand[0] =='r'){
        char*regNo = strtok(operand,"r");
        return atoi(regNo);
    } else return atoi(operand);
    return 0;
}

int8_t convertToInt(char* operand, CPU *cpu){ // handles binary and hex numbers
    if (operand[0] =='*'){ // " * " symbolize memory locations in ram
        if ((operand[1] == '0') && (operand[2] == 'x' || operand[2] == 'X')) {
            long decNumberLong = strtol(operand+1, NULL, 16);
            return (int8_t)decNumberLong;
        } else if (operand[1] == 'b' || operand[1] == 'B') {
            long decNumberLong = strtol(operand + 2, NULL, 2);
            return (int8_t)decNumberLong;
        } else if (operand[1] == 'r') {
            long decNumberLong = strtol(operand + 2, NULL, 10);
            return cpu->gpRegs[decNumberLong];
        } else {
            long decNumberLong = strtol(operand+1, NULL, 10);
            return (int8_t)decNumberLong;
        }
    } else {
        if ((operand[0] == '0') && (operand[1] == 'x' || operand[1] == 'X')) {
            long decNumberLong = strtol(operand, NULL, 16);
            return (int8_t)decNumberLong;
        } else if (operand[0] == 'b' || operand[0] == 'B') {
            long decNumberLong = strtol(operand + 1, NULL, 2);
            return (int8_t)decNumberLong;
        } else if (operand[0] == 'r') {
            long decNumberLong = strtol(operand + 1, NULL, 10);
            return (int8_t)decNumberLong;
        } else {
            long decNumberLong = strtol(operand, NULL, 10);
            return (int8_t)decNumberLong;
        }
    }
}

// INSTRUCTIONS _____________________________________________________________________________________________

void jumpInst(DecodedInst* inst ,CPU* cpu){ // overrites program counter with chosen instruction 
    int8_t destination = convertToInt(inst->operand1,cpu);
    cpu->isJumping = true;

    if ((destination >= 0) && (destination < RAM_SIZE/2)){ // can only jump into read only memory
        cpu->programCounter = destination;
    }
}

void jumpCondInst(DecodedInst* inst, CPU* cpu){ // conditional jmps
    switch(inst->opcodeNo){
        case JMP_ABV: if (!cpu->zeroFlag && !cpu->negativeFlag) jumpInst(inst,cpu); break;
        case JMP_NEG: if (cpu->negativeFlag) jumpInst(inst,cpu); break;
        case JMP_OFW: if (cpu->overflowFlag) jumpInst(inst,cpu); break;
        case JMP_ZRO: if (cpu->zeroFlag) jumpInst(inst,cpu); break;
        default: cpu->errorFlag = true; printError("\nERROR: INVALID JMP OPERATION");  break;
    }
}

void loadInst(DecodedInst *inst, CPU *cpu){ // take thing from ram and store in reg
    int8_t reg = getRegNo(inst->operand1); // reg val in mem location is moved to 
    int8_t input = convertToInt(inst->operand2,cpu);
    cpu->gpRegs[reg] = (inst->operand2[0] == '*') ? cpu->ram[input][0] : input;
}

void storeInst(DecodedInst *inst, CPU *cpu){ // take thing from reg and store in ram
    uint8_t destination = convertToInt(inst->operand1,cpu); // memory location 
    int8_t input; // value to be moved
        
    if (inst->operand2[0] =='r'){ 
        char*regNo = strtok(inst->operand2,"r");
        input = cpu->gpRegs[atoi(regNo)];
    } else input = convertToInt(inst->operand2,cpu);

    if ((destination < RAM_SIZE) && (destination > RAM_SIZE/2)) cpu->ram[destination][0] = input; // move to second half of ram
    else cpu->errorFlag = true; printError("\nERROR: MEMORY DESTINATION OUT OF BOUNDS\n"); 
}

void movInst(DecodedInst *inst, CPU *cpu){
    uint8_t destination = getRegNo(inst->operand1);
    uint8_t location = getRegNo(inst->operand2);
    if (((destination < CPU_REG_NO) && (destination >= 0)) && ((location<CPU_REG_NO) && (location>=0))){
        cpu->gpRegs[destination] = cpu->gpRegs[location];
    } else cpu->errorFlag = true; printError("\nERROR: MEMORY DESTINATION OUT OF BOUNDS\n"); 
}

void arithmeticInst(DecodedInst *inst, CPU *cpu){  // arithmetic and logical ops
    ALUResults alu = {0}; // init ALU
    int8_t inputA;
    int8_t inputB;
    uint8_t regOut = getRegNo(inst->operand1);

    if (inst->operand3[0] =='r'){ // get value in reg if wanted
        char*regNo = strtok(inst->operand3,"r");
        inputB = cpu->gpRegs[atoi(regNo)];
    } else inputB = convertToInt(inst->operand3,cpu);

    if (inst->operand2[0] =='r'){ 
        char*regNo = strtok(inst->operand2,"r");
        inputA = cpu->gpRegs[atoi(regNo)];
    } else inputA = convertToInt(inst->operand2,cpu);

    switch(inst->opcodeNo){
        case ADD: ALUEmulator(inputA,inputB,OP_ADD,cpu); break;
        case SUB: ALUEmulator(inputA,inputB,OP_SUB,cpu); break;
        case AND: ALUEmulator(inputA,inputB,OP_AND,cpu); break;
        case MUL: ALUEmulator(inputA,inputB,OP_MULT,cpu);break;
        case OR:  ALUEmulator(inputA,inputB,OP_OR,cpu);  break;
        case XOR: ALUEmulator(inputA,inputB,OP_XOR,cpu); break;
        case EQU: ALUEmulator(inputA,inputB,OP_EQU,cpu); break;
        default: cpu->errorFlag = true; printError("\nERROR: INVALID ARITHMETIC OPERATION\n");  break;
    }
    cpu->gpRegs[regOut] = cpu->alu.output; // put result in desired reg
}

#endif