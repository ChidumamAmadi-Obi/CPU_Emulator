#ifndef ALU_EMULATOR
#define ALU_EMULATOR

#include "config.h"

// 8 bit ALU handles SIGNED arithmetic

void clearFlags(ALUResults* results){ // clears all status flags
    results->carryFlag = false;    
    results->overflowFlag = false; 
    results->errorFlag = false;
    results->negativeFlag = false;
    results->zeroFlag = false;
}

bool detectOverflow(int8_t inputA, int8_t inputB, ALUOperations operation, ALUResults* results ){ // detects overflow whith arithmetic ops
    bool signA = (inputA & MSB) != 0; // checks signs...
    bool signB = (inputB & MSB) != 0;
    bool signR = (results->output & MSB) != 0;

    if (operation == OP_ADD) { // if adding
        // when adding two positive and the result is a negative
        // when adding two negatives and the result if a positive
        return (signA == signB) && (signA != signR);

    } else if (operation == OP_SUB) { // if subtracting
        int8_t negB = ~inputB + 1;  // get the Two's complement of b (binary representation of a negative number)
        bool signNegB = (negB & MSB) != 0; // find the dign of the two's comp of b
        return (signA == signNegB) && (signA != signR);
    } else if (operation == OP_MULT) { // if multiplying
        return (results->tempResult > 127) || (results->tempResult < MIN_NUMBER);
    } else return false;   
}

ALUResults ALUEmulator(int8_t inputA, int8_t inputB, ALUOperations operation) {
    ALUResults results = {0}; // initializes all members with zero
    bool isBitwiseOp = false;

    switch(operation){
        case OP_ADD: 
            results.tempResult = (uint16_t)(inputA) + (uint16_t)(inputB); // temp result to look at extra bits
            results.output = (int8_t)(results.tempResult & 0xFF); // and this with 0xFF because c will mess it up if i dont
            results.carryFlag = (results.tempResult > 0xFF);
            break;

        case OP_SUB:
            results.tempResult = (uint16_t)(inputA) - (uint16_t)(inputB);
            results.output = (int8_t)(results.tempResult & 0xFF);
            results.carryFlag = (inputB > inputA);
            break;

        case OP_MULT:
            results.tempResult = (int16_t)(inputA) * (int16_t)(inputB);
            results.output = (int8_t)(results.tempResult & 0xFF);
            results.carryFlag = (results.tempResult > 0xFF);
            break;
        
        case OP_DIVIDE: 
            if (inputB == 0) { // you cant divide something with zero
                    results.errorFlag = true;
                    results.output = 0;
                } else {
                    results.output = inputA / inputB;
                    if (inputA == MIN_NUMBER && inputB == -1) {
                        results.errorFlag = true;
                    }
                }
        break;

        case OP_ROTATE_LEFT: // rotates once
            results.carryFlag = (inputA & MSB) != 0;  // MSB becomes carry
            results.output = (inputA << 1) | (results.carryFlag ? 1 : 0);
            results.overflowFlag = false;
            break;

        case OP_ROTATE_RIGHT:
            results.carryFlag = (inputA & LSB) != 0;  // LSB becomes carry
            results.output = (inputA >> 1) | (results.carryFlag ? MSB : 0);
            results.overflowFlag = false;
            break;

        case OP_AND: case OP_NAND: case OP_OR: case OP_XOR: case OP_NOR: case OP_XNOR: case OP_EQU: case OP_GREATER_THAN: case OP_LESS_THAN: 
            isBitwiseOp = true; // handle bitwise operations..
            switch(operation) {
                case OP_AND:            results.output = inputA&inputB; break;
                case OP_NAND:           results.output = ~(inputA&inputB); break;
                case OP_OR:             results.output = inputA|inputB; break;
                case OP_XOR:            results.output = inputA^inputB; break;
                case OP_NOR:            results.output = ~(inputA|inputB); break;
                case OP_XNOR:           results.output = ~(inputA^inputB);  break;
                case OP_EQU:            results.output = (inputA == inputB) ? 1 : 0; break;
                case OP_GREATER_THAN:   results.output = (inputA > inputB) ? 1 : 0; break;
                case OP_LESS_THAN:      results.output = (inputA < inputB) ? 1 : 0; break;
            }
            clearFlags(&results); // no flags for bitwise operations
            break;        
        
        default: 
            results.errorFlag = true; 
            results.output = 0; 
            break;
    }

    if (!results.errorFlag && !isBitwiseOp) { // update flags if no errors and no bitwise ops
        results.overflowFlag = detectOverflow(inputA,inputB,operation,&results);
        results.zeroFlag = (results.output == 0) ? true : false;
        results.negativeFlag = (results.output & MSB) != 0;  // Checks MSB (bit 7)
    }
    return results;
}

#endif