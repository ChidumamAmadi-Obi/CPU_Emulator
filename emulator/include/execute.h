#pragma once 

#include "config.h"
#include "ALU.h"
#include "memory.h"

bool isInMemoryBounds(int memLocation,MemoryBoundsChecking loc){
    switch(loc){
        case CHECK_IF_IN_RAM:
            if (memLocation > ROM_SIZE && memLocation <= RAM_SIZE)
            return 1; break;

        case CHECK_IF_IN_ROM:
            if (memLocation >= 0 && memLocation < ROM_SIZE)
            return 1; break;

        case CHECK_IF_VALID_REGISTER:
            if (memLocation >= 0 && memLocation <= CPU_REG_NO)
            return 1; break;

        case CHECK_IF_VALID_POINTER:
            if (memLocation >= PTR_R0 && memLocation <= PTR_R15)
            return 1; break;

        default: return 0; break;
    }
    return 0;
}

// CPU INSTRUCTIONS _____________________________________________________________________________________________
void loadImmInst(CPU * cpu){ // take literal number and store in register
    uint8_t destinationReg = cpu->instructionReg[1]; // reg number the input is moved to 
    uint8_t inputLiteral = cpu->instructionReg[2];

    if(!isInMemoryBounds(destinationReg,CHECK_IF_VALID_REGISTER)) {
        cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS;
        return; 
    }

    cpu->gpRegs[destinationReg] = inputLiteral;
}
void loadInst(CPU *cpu){ // take thing from ram and store in reg
    uint8_t destinationReg = cpu->instructionReg[1]; // reg number the input is moved to 
    uint8_t input = cpu->instructionReg[2];
    uint8_t memLocation =0; // stores memory location held in pointer

    if(!isInMemoryBounds(destinationReg,CHECK_IF_VALID_REGISTER)) { 
        cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS; // dest reg out of bounds
        return;
    }

    if(isInMemoryBounds(input,CHECK_IF_VALID_POINTER)){ // if valid pointer
        memLocation=cpu->gpRegs[input-CPU_REG_NO];// get mem location in register
        if(isInMemoryBounds(memLocation,CHECK_IF_IN_RAM)){
            cpu->gpRegs[destinationReg] = cpu->ram[memLocation];
            return;
        }
    }
    if (isInMemoryBounds(input,CHECK_IF_IN_RAM)){// if not pointer chck if valid ram location
        cpu->gpRegs[destinationReg] = cpu->ram[input];
        return;
    }

    cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS; return;
}
void storeInst(CPU *cpu){ // take thing from reg and store in ram
    uint8_t destination = cpu->instructionReg[1]; // memory location 
    uint8_t input = cpu->instructionReg[2]; // value to be moved

    if(!isInMemoryBounds(destination,CHECK_IF_IN_RAM) || 
       !isInMemoryBounds(input,CHECK_IF_VALID_REGISTER)) { // if not valid register or mem location
           cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS;
           return;        
       }

    cpu->ram[destination] = cpu->gpRegs[input];
}
void movInst(CPU *cpu){ // copy value in one reg into another
    uint8_t destination = cpu->instructionReg[1];
    uint8_t location = cpu->instructionReg[2];

    if ( !isInMemoryBounds(destination,CHECK_IF_VALID_REGISTER) || 
         !isInMemoryBounds(location,CHECK_IF_VALID_REGISTER)){
            cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS;
            return;
        }
        cpu->gpRegs[destination] = cpu->gpRegs[location];
}

void jumpInst(CPU*cpu) { // overrite ram ptr, will jump to instruction in memory if condition is true
    uint32_t destination = cpu->instructionReg[1];

    if (!isInMemoryBounds(destination,CHECK_IF_IN_ROM)) {
        cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS;
        return;
    }

    switch(cpu->instructionReg[0]) {
        case JMP_ABV: if (!cpu->negativeFlag && !cpu->zeroFlag) cpu->programCounter=destination; break;
        case JMP_NEG: if (cpu->negativeFlag)                    cpu->programCounter=destination; break;
        case JMP_OFW: if (cpu->overflowFlag)                    cpu->programCounter=destination; break;
        case JMP_ZRO: if (cpu->zeroFlag)                        cpu->programCounter=destination; break;

        case JMP: cpu->programCounter=destination; break;
        case RET: cpu->programCounter=cpu->nextInst; break;// return from subroutine
        case CALL: 
            cpu->nextInst = cpu->programCounter; // stores location of next instruction
            cpu->programCounter=destination; // jumps to start of subroutine
            break;

        default:  cpu->fatalError=ERROR_EXECUTING_INTRUCTION; break;
    }
}

void arithmeticInst(CPU *cpu){  // arithmetic and logical ops
    ALUResults alu = {0}; // init ALU
    uint8_t regOut = cpu->instructionReg[1];
    uint8_t regInA = cpu->instructionReg[2];
    int8_t inputA;
    int8_t inputB;

    if(!isInMemoryBounds(regInA,CHECK_IF_VALID_REGISTER) ||
       !isInMemoryBounds(regOut,CHECK_IF_VALID_REGISTER)){
        cpu->fatalError=ERROR_MEMORY_OUT_OF_BOUNDS;
        return;
    }

    inputA = (int8_t)cpu->gpRegs[regInA]; // input a always refers to a register

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
