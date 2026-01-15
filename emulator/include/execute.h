#pragma once 

#include "config.h"
#include "ALU.h"
#include "memory.h"

// INSTRUCTIONS _____________________________________________________________________________________________

void loadImmInst(CPU * cpu){ // take literal number and store in register
    uint8_t destinationReg = cpu->instructionReg[1]; // reg number the input is moved to 
    uint8_t inputLiteral = cpu->instructionReg[2];

    if(destinationReg < 0 || destinationReg > CPU_REG_NO ) { // check if within memory bounds
        cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS;
        return;
    } 
    cpu->gpRegs[destinationReg] = inputLiteral;
}
void loadInst(CPU *cpu){ // take thing from ram and store in reg
    uint8_t destinationReg = cpu->instructionReg[1]; // reg number the input is moved to 
    uint8_t input = cpu->instructionReg[2];
    uint8_t memLocation =0; // if pointer

    if (destinationReg < 0 || destinationReg > CPU_REG_NO) {
        cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS; // dest reg out of bounds
        return;
    }
    if (input>=PTR_R0 && input<=PTR_R15 ) { // if ptr
        memLocation=cpu->gpRegs[input-CPU_REG_NO]; // get mem location in register
        if (memLocation>RAM_SIZE/2 && memLocation<RAM_SIZE) {
            cpu->gpRegs[destinationReg] = cpu->ram[memLocation];
            return;
        } 
    } 
    if (input>RAM_SIZE/2 && input<RAM_SIZE) { // if ram location
        cpu->gpRegs[destinationReg] = cpu->ram[input];
        return;
    } 

    cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS; return;
}
void storeInst(CPU *cpu){ // take thing from reg and store in ram
    uint8_t destination = cpu->instructionReg[1]; // memory location 
    uint8_t input = cpu->instructionReg[2]; // value to be moved

    if ((destination < RAM_SIZE/2) || (destination > RAM_SIZE) ||
         input < 0  || input > R15 ) { // if access memory out of bounds
           cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS;
           return;
    } 
    cpu->ram[destination] = cpu->gpRegs[input];
}
void movInst(CPU *cpu){ // copy value in one reg into another
    uint8_t destination = cpu->instructionReg[1];
    uint8_t location = cpu->instructionReg[2];

    if (((destination < CPU_REG_NO) && (destination >= 0)) && ((location<CPU_REG_NO) && (location>=0))){
        cpu->gpRegs[destination] = cpu->gpRegs[location];
    } else cpu->fatalError = ERROR_MEMORY_OUT_OF_BOUNDS;  
}

void jumpInst(CPU*cpu) { // overrite ram ptr, will jump to instruction in memory if condition is true
    switch(cpu->instructionReg[0]) {
        case JMP_ABV: if (!cpu->negativeFlag && !cpu->zeroFlag) cpu->programCounter=cpu->instructionReg[1]; return;
        case JMP_NEG: if (cpu->negativeFlag)                    cpu->programCounter=cpu->instructionReg[1]; return;
        case JMP_OFW: if (cpu->overflowFlag)                    cpu->programCounter=cpu->instructionReg[1]; return;
        case JMP_ZRO: if (cpu->zeroFlag)                        cpu->programCounter=cpu->instructionReg[1]; return;
        case JMP:                                               cpu->programCounter=cpu->instructionReg[1]; return;
        default:  cpu->fatalError=ERROR_EXECUTING_INTRUCTION; return;
    }
}

void arithmeticInst(CPU *cpu){  // arithmetic and logical ops
    ALUResults alu = {0}; // init ALU
    uint8_t regOut = cpu->instructionReg[1];
    int8_t inputA = (int8_t)cpu->gpRegs[cpu->instructionReg[2]]; // input a always refers to a register
    int8_t inputB;

    switch(cpu->instructionReg[0]){
        case DIVI: inputB=(int8_t)cpu->instructionReg[3]; ALUEmulator(inputA,inputB,OP_DIVIDE,cpu); break;
        case EQUI: inputB=(int8_t)cpu->instructionReg[3]; ALUEmulator(inputA,inputB,OP_EQU,cpu); break;
        case XORI: inputB=(int8_t)cpu->instructionReg[3]; ALUEmulator(inputA,inputB,OP_XOR,cpu); break;
        case ORI:  inputB=(int8_t)cpu->instructionReg[3]; ALUEmulator(inputA,inputB,OP_OR,cpu); break;
        case MULI: inputB=(int8_t)cpu->instructionReg[3]; ALUEmulator(inputA,inputB,OP_MULT,cpu); break;
        case ANDI: inputB=(int8_t)cpu->instructionReg[3]; ALUEmulator(inputA,inputB,OP_AND,cpu); break;
        case SUBI: inputB=(int8_t)cpu->instructionReg[3]; ALUEmulator(inputA,inputB,OP_SUB,cpu); break;
        case ADDI: inputB=(int8_t)cpu->instructionReg[3]; ALUEmulator(inputA,inputB,OP_ADD,cpu); break;

        case ADD:  inputB=(int8_t)cpu->gpRegs[cpu->instructionReg[3]]; ALUEmulator(inputA,inputB,OP_ADD,cpu); break;
        case SUB:  inputB=(int8_t)cpu->gpRegs[cpu->instructionReg[3]]; ALUEmulator(inputA,inputB,OP_SUB,cpu); break;
        case AND:  inputB=(int8_t)cpu->gpRegs[cpu->instructionReg[3]]; ALUEmulator(inputA,inputB,OP_AND,cpu); break;
        case MUL:  inputB=(int8_t)cpu->gpRegs[cpu->instructionReg[3]]; ALUEmulator(inputA,inputB,OP_MULT,cpu);break;
        case OR:   inputB=(int8_t)cpu->gpRegs[cpu->instructionReg[3]]; ALUEmulator(inputA,inputB,OP_OR,cpu);  break;
        case XOR:  inputB=(int8_t)cpu->gpRegs[cpu->instructionReg[3]]; ALUEmulator(inputA,inputB,OP_XOR,cpu); break;
        case EQU:  inputB=(int8_t)cpu->gpRegs[cpu->instructionReg[3]]; ALUEmulator(inputA,inputB,OP_EQU,cpu); break;
        case DIV:  inputB=(int8_t)cpu->gpRegs[cpu->instructionReg[3]]; ALUEmulator(inputA,inputB,OP_DIVIDE,cpu); break;

        default: cpu->fatalError = ERROR_INVALID_ARITHMETIC_OPERATION; break;
    }
    cpu->gpRegs[regOut] = cpu->alu.output; // put result in desired reg
}
