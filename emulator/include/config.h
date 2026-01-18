#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "color.h"

// debugging
#define SHOW_ERRORS 1
#define SHOW_RAM 0
#define SHOW_REGISTERS 1
#define SHOW_FLAGS 0
#define SHOW_PC 1 // print each executed instruction
#define SHOW_METRICS 1 // print execution time and completed cycles

#define PRINT_ALU_ERRORS 0

// alu constants
#define MSB 0x80
#define LSB 0x01
#define MAX_NUMBER 127
#define MIN_NUMBER -128

// memory constants
#define RAM_SIZE 0xFF // 255 bytes
#define ROM_SIZE RAM_SIZE/2 // can adjust if you want
#define INST_LENGTH 4 // each instruction has a maximum length of 4 bytes
#define CPU_REG_NO 16

#if PRINT_ALU_ERRORS == 1
#define printError(x) printf(x)
#else
#define printError(x)
#endif

typedef enum{
    HALT,    
    STR,
    LD,
    JMP,
    MOV,
    JMP_OFW,
    JMP_ZRO,
    JMP_NEG,
    JMP_ABV, // jump if both the zero and negative flags are false
    ADD,
    SUB,
    MUL,
    AND,
    OR,
    XOR,
    EQU,
    DIV,

    LI, // load immediate
    ADDI,
    SUBI,
    MULI,
    ANDI,
    ORI,
    XORI,
    EQUI,
    DIVI,
    CALL,
    RET

}CPUInstruction;
typedef enum{
    R0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    R14,
    R15,
    PTR_R0,
    PTR_R1,
    PTR_R2,
    PTR_R3,
    PTR_R4,
    PTR_R5,
    PTR_R6,
    PTR_R7,
    PTR_R8,
    PTR_R9,
    PTR_R10,
    PTR_R11,
    PTR_R12,
    PTR_R13,
    PTR_R14,
    PTR_R15
}Registers;
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
typedef enum{ // stop running cpu if one of these errors show up
    NONE,
    ERROR_LOADING_PROGRAM,
    ERROR_PROGRAM_SIZE,
    ERROR_FETCHING_INSTRUCTION,
    ERROR_DECODING_INSTRUCTION,
    ERROR_EXECUTING_INTRUCTION,
    ERROR_MEMORY_OUT_OF_BOUNDS,
    ERROR_INVALID_ARITHMETIC_OPERATION
}FatalErrors;
typedef enum{
    CHECK_IF_IN_ROM,
    CHECK_IF_IN_RAM,
    CHECK_IF_VALID_REGISTER,
    CHECK_IF_VALID_POINTER
}MemoryBoundsChecking;

typedef struct{ // records metrics
    uint32_t cycles;
    uint32_t executedInstructions;
    size_t bytesInProgram; // stores program size in bytes
    double exetime;
}Preformance;
typedef struct{ // alu results
    int8_t output;
    int16_t tempResult;
    bool carryFlag;
    bool errorFlag;
}ALUResults;
typedef struct{ // CPU variables
    ALUResults alu;
    Preformance metrics;
    uint32_t programCounter; // tracks byte position in ram
    uint32_t nextInst; // location of next instruction after subroutine is called
    uint8_t fatalError;
    uint8_t instructionReg[INST_LENGTH];
    uint8_t gpRegs[CPU_REG_NO];
    uint8_t ram[RAM_SIZE];  
    
    bool errorFlag; // alu flags
    bool zeroFlag;
    bool overflowFlag;
    bool negativeFlag;

    bool isRunning;
}CPU;