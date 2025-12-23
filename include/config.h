#ifndef CONFIG
#define CONFIG

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// debugging
#define PRINT_RAM_MODE 1 // 0: dont print, 1: char, 2: int, 3:hex 
#define PRINT_PC 0 // print each executed instruction
#define PRINT_ERRORS 0

// ascii stuff
#define ASCII_SPACE 0x20
#define ASCII_SEMI_COLON 0x3b

// alu constants
#define MSB 0x80
#define LSB 0x01
#define MAX_NUMBER 127
#define MIN_NUMBER -128

// memory constants
#define RAM_SIZE 0xFF
#define INST_LENGTH 24
#define CPU_REG_NO 16

#if PRINT_ERRORS == 1
#define printError(x) printf(x)
#else
#define printError(x)
#endif

typedef enum{
    STR,
    LD,
    JMP,
    MOV,
    HALT,

    JMP_OFW,
    JMP_ZRO,
    JMP_NEG,
    JMP_ABV, // jump if neither the zero or negative flags are true

    ADD,
    SUB,
    MUL,
    AND,
    OR,
    XOR,
    EQU,
    DIV
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
typedef enum{ // for visualizing sata in ram
    NONE=0,
    CHAR,
    INTEGER,
    HEX
}MemPrintModes;

typedef struct{ // records metrics
    uint32_t cycles;
    uint32_t executedInstructions;
}Preformance;
typedef struct{ // alu results
    int8_t output;
    int16_t tempResult;
    bool carryFlag;
    bool errorFlag;
}ALUResults;
typedef struct{ // parsed instruction
    CPUInstruction opcodeNo;
    char*opcode;
    char*operand1;
    char*operand2;
    char*operand3;
}DecodedInst;
typedef struct{ // CPU variables
    ALUResults alu;
    Preformance metrics;
    uint8_t instructionReg[INST_LENGTH];
    int8_t gpRegs[CPU_REG_NO];
    int8_t ram[RAM_SIZE][INST_LENGTH]; // 2d ram unconventional but oh well 
    uint8_t programCounter;

    bool errorFlag; // alu flags
    bool zeroFlag;
    bool overflowFlag;
    bool negativeFlag;

    bool isRunning;
    bool isJumping; // keep track of jmp so pc doesnt accidently inc twice
}CPU;


#endif

// https://youtu.be/rdKX9hzA2lU?si=gsVF8THibba89D1V 