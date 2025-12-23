#ifndef ALU_EMULATOR
#define ALU_EMULATOR

#include "config.h"

// 8 bit ALU handles SIGNED arithmetic

void clearFlags(CPU* cpu){ // clears all alu status flags
    cpu->alu.errorFlag = false;
    cpu->alu.carryFlag = false;    

    cpu->overflowFlag = false; 
    cpu->negativeFlag = false;
    cpu->zeroFlag = false;
}

bool detectOverflow(int8_t inputA, int8_t inputB, ALUOperations operation, CPU* cpu ){ // detects overflow whith arithmetic ops
    bool signA = (inputA & MSB) != 0; // checks signs...
    bool signB = (inputB & MSB) != 0;
    bool signR = (cpu->alu.output & MSB) != 0;

    if (operation == OP_ADD) { // if adding
        // when adding two positive and the result is a negative
        // when adding two negatives and the result if a positive
        return (signA == signB) && (signA != signR);

    } else if (operation == OP_SUB) { // if subtracting
        int8_t negB = ~inputB + 1;  // get the Two's complement of b (binary representation of a negative number)
        bool signNegB = (negB & MSB) != 0; // find the dign of the two's comp of b
        return (signA == signNegB) && (signA != signR);
    } else if (operation == OP_MULT) { return (cpu->alu.tempResult > 127) || (cpu->alu.tempResult < MIN_NUMBER);
    } else return false;   
}

void ALUEmulator(int8_t inputA, int8_t inputB, ALUOperations operation, CPU *cpu) {
    bool isBitwiseOp = false;

    switch(operation){
        case OP_ADD: 
            cpu->alu.tempResult = (int16_t)(inputA) + (int16_t)(inputB); // temp result to look at extra bits
            cpu->alu.output = (int8_t)(cpu->alu.tempResult & 0xFF); // and this with 0xFF because c will mess it up if i dont
            cpu->alu.carryFlag = (cpu->alu.tempResult > 0xFF);
            break;

        case OP_SUB:
            cpu->alu.tempResult = (int16_t)(inputA) - (int16_t)(inputB);
            cpu->alu.output = (int8_t)(cpu->alu.tempResult & 0xFF);
            cpu->alu.carryFlag = (inputB > inputA);
            break;

        case OP_MULT:
            cpu->alu.tempResult = (int16_t)(inputA) * (int16_t)(inputB);
            cpu->alu.output = (int8_t)(cpu->alu.tempResult & 0xFF);
            cpu->alu.carryFlag = (cpu->alu.tempResult > 0xFF);
            break;
        
        case OP_DIVIDE: 
            if (inputB == 0) { // you cant divide something with zero
                    cpu->alu.errorFlag = true;
                    cpu->alu.output = 0;
                    printError("\nERROR: CAN'T DIVIDE BY ZERO");
                } else {
                    cpu->alu.output = inputA / inputB;
                    if (inputA == MIN_NUMBER && inputB == -1) cpu->alu.errorFlag = true;
                }
        break;

        case OP_ROTATE_LEFT: // rotates once
            cpu->alu.carryFlag = (inputA & MSB) != 0;  // MSB becomes carry
            cpu->alu.output = (inputA << 1) | (cpu->alu.carryFlag ? 1 : 0);
            cpu->overflowFlag = false;
            break;

        case OP_ROTATE_RIGHT:
            cpu->alu.carryFlag = (inputA & LSB) != 0;  // LSB becomes carry
            cpu->alu.output = (inputA >> 1) | (cpu->alu.carryFlag ? MSB : 0);
            cpu->overflowFlag = false;
            break;

        case OP_AND: case OP_NAND: case OP_OR: case OP_XOR: case OP_NOR: case OP_XNOR: case OP_EQU: case OP_GREATER_THAN: case OP_LESS_THAN: 
            isBitwiseOp = true; // handle bitwise operations..
            switch(operation) {
                case OP_AND:            cpu->alu.output = inputA&inputB; break;
                case OP_NAND:           cpu->alu.output = ~(inputA&inputB); break;
                case OP_OR:             cpu->alu.output = inputA|inputB; break;
                case OP_XOR:            cpu->alu.output = inputA^inputB; break;
                case OP_NOR:            cpu->alu.output = ~(inputA|inputB); break;
                case OP_XNOR:           cpu->alu.output = ~(inputA^inputB);  break;
                case OP_EQU:            cpu->alu.output = (inputA == inputB) ? 1 : 0; break;
                case OP_GREATER_THAN:   cpu->alu.output = (inputA > inputB) ? 1 : 0; break;
                case OP_LESS_THAN:      cpu->alu.output = (inputA < inputB) ? 1 : 0; break;
            }
            clearFlags(cpu); // no flags for bitwise operations
            break;        
        
        default: 
            cpu->alu.errorFlag = true; 
            printError("\nERROR: INVALID ALU OPERATION"); 
            break;
    }

    if (!cpu->alu.errorFlag && !isBitwiseOp) { // update flags if no errors and no bitwise ops
        cpu->overflowFlag = detectOverflow(inputA,inputB,operation,cpu);
        cpu->zeroFlag = (cpu->alu.output == 0) ? true : false;
        cpu->negativeFlag = (cpu->alu.output & MSB) != 0;  // Checks MSB (bit 7)
    } else if (cpu->alu.errorFlag) {
        cpu->errorFlag=true;
        cpu->alu.output=0;
    } 
}

#endif