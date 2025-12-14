#ifndef CONFIG
#define CONFIG

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SPACE 0x20
#define ASCII_SEMI_COLON 0x3b

// alu constants
#define MSB 0x80
#define LSB 0x01
#define MAX_NUMBER 127
#define MIN_NUMBER -128

// memory constants
#define PRINT_PROGRAM_MODE 3
#define RAM_SIZE 128
#define INST_LENGTH 16

typedef enum{
    STR=1,
    LD=2,
    JMP=3,
    HALT=4,

    JMP_OFW=5,
    JMP_ZRO=6,
    JMP_NEG=7,
    JMP_ABV=8,

    ADD=9,
    SUB=10,
    AND=11,
    OR=12,
    XOR=13,
    EQU=14
}CPUInstruction;
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
typedef enum{
    CHAR,
    INTEGER,
    HEX
}MemPrintModes;

typedef struct{
    int8_t output;
    int16_t tempResult;
    bool zeroFlag;
    bool carryFlag;
    bool overflowFlag;
    bool negativeFlag;
    bool errorFlag;
}ALUResults;
typedef struct{
    uint8_t instructionReg[INST_LENGTH];
    uint8_t programCounter;
    uint8_t gpRegs[16];
    uint8_t ram[RAM_SIZE][INST_LENGTH];
    bool errorFlag;
    bool isRunning;
}CPU;
typedef struct{
    CPUInstruction opcodeNo;
    char*opcode;
    char*operand1;
    char*operand2;
    char*operand3;
}DecodedInst;
CPU cpu;

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

/*
future opcodes
JMP - overwrites address register (jumps to speficied address in rom)
STR - store
LD  - load
HALT- stop program

JMP_OFW
JMP_ZRO
JMP_NEG
JMP_ABV

*/