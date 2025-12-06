#ifndef CONFIG
#define CONFIG

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MSB 0x80
#define LSB 0x01
#define MAX_NUMBER 127
#define MIN_NUMBER -128

typedef struct{
    int8_t output;
    int16_t tempResult;
    bool zeroFlag;
    bool carryFlag;
    bool overflowFlag;
    bool negativeFlag;
    bool errorFlag;
}ALUResults;

typedef enum{
    OP_ADD,              
    OP_SUB, 

    OP_AND,              
    OP_OR,               
    OP_XOR,              
    OP_NAND,             
    OP_NOR,              
    OP_XNOR,              
    OP_EQU,              
    OP_GREATER_THAN,     
    OP_LESS_THAN,    

    OP_ROTATE_RIGHT,     
    OP_ROTATE_LEFT,      

    OP_DIVIDE,           
    OP_MULT,             
}ALUOperations;

typedef struct{
    uint8_t instructionReg;
    uint8_t *programCounter;
    uint8_t gpRegs[16];
}CPU;

typedef struct {
    uint8_t ram[32];
    uint8_t rom[32];
}Memory;

extern Memory memory;
extern CPU cpu;

#endif

/*
PLAN 
Phase 1: 
    ALU

Phase 2: 
    Program Counter (PC)
    Instruction Register (IR)
    General Purpose Registers
    Memory (RAM/ROM)
    Control Unit (instruction decoder)

Phase 3: 
    Fetch-decode-execute cycle
    Addressing modes
    Branch/jump logic

Phase 4: 
    Clock/timing simulation
*/