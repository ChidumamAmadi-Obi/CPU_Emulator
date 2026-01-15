#pragma once 

#include <bits/stdc++.h>
#include <unordered_map> // to use hashmaps
#include <vector>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // for pretty terminal colors in windows

// configure 
#define SHOW_ERRORS 1
#define SHOW_SYMBOL_TABLE 1
#define SHOW_GENERATED_BINARY 1
#define DEBUG_RAW_ASM 0
#define DEBUG_TOKENIZER 0

#define DEBUG_FIRST_PASS 0
#define DEBUG_SECOND_PASS 0

// macros
#define INVALID -1
#define UNDEFINED_LABEL -1
#define INVALID_LITERAL -999

using namespace std;

//_________________________________________________________________________________________________
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
    DIVI
}Mnemonics;
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
typedef enum{ // if error program should stop immediatly
    NONE,
    SYNTAX_ERROR,
    LOADING_PROGRAM_ERROR,
    EXPORTING_BINARY_ERROR,
    SYMBOL_ERROR,
    BIN_GEN_ERROR
}ProgramErrors;
typedef enum{
    BLUE=1,
    GREEN=2,
    CYAN=3,
    RED=4,
    PURPLE=5,
    DARK_YELLOW=6,
    DEFAULT_WHITE=7,
    GREY=8,
    BRIGHT_BLUE=9,
    BRIGHT_GREEN=10,
    BRIGHT_CYAN=11,
    BRIGHT_RED=12,
    PINK=13,
    YELLOW=14,
    BRIGHT_WHITE=15,
}TerminalColors;

//_________________________________________________________________________________________________
typedef struct{
    string rawAsm = "";
    string invalidToken="";
    string invalidLabel="";
    uint16_t sizeOfProgam=0; // size of program in bytes
    vector <string> tokens;
    vector <uint8_t> machineCode; // each token will take up 8 bytes
    unordered_map<string,int8_t> symbolTable; 
}Program;
typedef struct{
    Program program;
    ProgramErrors errorCode = NONE;
    HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE); // for changing terminal colors
}Assembler;
typedef struct{
    unordered_map<string,Mnemonics> mnemonicMap = {
        {"STR", STR},
        {"LD", LD},
        {"JMP", JMP},
        {"MOV", MOV},
        {"HALT", HALT},
        {"JMP_OFW", JMP_OFW},
        {"JMP_ZRO", JMP_ZRO},
        {"JMP_NEG", JMP_NEG},
        {"JMP_ABV", JMP_ABV},
        {"ADD", ADD},
        {"SUB", SUB},
        {"MUL", MUL},
        {"AND", AND},
        {"OR", OR},
        {"XOR", XOR},
        {"EQU", EQU},
        {"DIV", DIV},
        {"LI",LI},
        {"ADDI",ADDI},
        {"SUBI",SUBI},
        {"MULI",MULI},
        {"ANDI",ANDI},
        {"OR",ORI},
        {"XORI",XORI},
        {"EQUI",EQUI},
        {"DIVI",DIVI}};
    unordered_map<string,Registers> regMap = {
        {"r0", R0},
        {"r1",R1},
        {"r2",R2},
        {"r3",R3},
        {"r4",R4},
        {"r5",R5},
        {"r6",R6},
        {"r7",R7},
        {"r8",R8},
        {"r9",R9},
        {"r10",R10},
        {"r11",R11},
        {"r12",R12},
        {"r13",R13},
        {"r14",R14},
        {"r15",R15},
        {"*r0",PTR_R0},
        {"*r1",PTR_R1},
        {"*r2",PTR_R2},
        {"*r3",PTR_R3},
        {"*r4",PTR_R4},
        {"*r5",PTR_R5},
        {"*r6",PTR_R6},
        {"*r7",PTR_R7},
        {"*r8",PTR_R8},
        {"*r9",PTR_R9},
        {"*r10",PTR_R10},
        {"*r11",PTR_R11},
        {"*r12",PTR_R12},
        {"*r13",PTR_R13},
        {"*r14",PTR_R14},
        {"*r15",PTR_R15}};
}Maps;

/*
https://www.geeksforgeeks.org/compiler-design/introduction-of-assembler/

1. + make lexer/tokenizer 
2. + make symbol table
3. + first pass ( calc instruction sizes & get label addfresses in symbol table )
4. + get mnemonics int o machine code
5. + second pass ( replace mnemonics w opcodes & replace labels w acctual addresses )
6. + output bin/hex machine code to a file
*/