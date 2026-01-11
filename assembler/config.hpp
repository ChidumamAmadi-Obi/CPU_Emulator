#pragma once 

#include <bits/stdc++.h>
#include <unordered_map> // to use hashmaps
#include <vector>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define SHOW_ERRORS 1
#define SHOW_SYMBOL_TABLE 1
#define DEBUG_RAW_ASM 0
#define DEBUG_TOKENIZER 0
#define DEBUG_BIN_OUT 0

#define DEBUG_FIRST_PASS 0
#define DEBUG_SECOND_PASS 0

typedef enum{
    STR,
    LD,
    JMP,
    MOV,
    HALT,
    JMP_OFW,
    JMP_ZRO,
    JMP_NEG,
    JMP_ABV, 
    ADD,
    SUB,
    MUL,
    AND,
    OR,
    XOR,
    EQU,
    DIV
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
    FILE_ERROR,
    SYMBOL_ERROR,
    BIN_GEN_ERROR
}ProgramErrors;

typedef struct{
    string rawAsm = "";
    string invalidToken="";
    vector <string> tokens;
    unordered_map<string,int8_t> symbolTable; 
}Program;
typedef struct{
    Program program;
    ProgramErrors errorCode = NONE;
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
        {"DIV", DIV}};
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
3. + first pass ( calc instruction sizes & get label addresses in symbol table )
4. get mnemonics int o machine code
5. second pass ( replace mnemonics w opcodes & replace labels w acctual addresses )
6. output bin/hex machine code to a file
*/