#pragma once 

using namespace std;

#include <bits/stdc++.h>
#include <unordered_map> // to use hashmaps

#include <stdio.h>
#include <stdlib.h>

#define SHOW_ERRORS 1
#define DEBUG_RAW_ASM 1
#define DEBUG_PROCESSES_ASM 0
#define DEBUG_TOKENIZER 0
#define DEBUG_SYMBOLS 0
#define DEBUG_BIN_OUT 0

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
    NONE,
    SYNTAX_ERROR,
    FILE_ERROR,
    SYMBOL_ERROR,
    BIN_GEN_ERROR
}ProgramErrors;

typedef struct{
    string rawAsm = "";
    unordered_map<string,int> symbolTable; 
}Program;
typedef struct{
    Program program;
    ProgramErrors errorCode = NONE;
}Assembler;

/*
1. make lexer/tokenizer
2. make symbol table
3. first pass ( calc instruction sizes & get label addresses in symbol table )
4. get mnemonics int o machine code
5. second pass ( replace mnemonics w opcodes & replace labels w acctual addresses )
6. output bin/hex machine code to a file
*/