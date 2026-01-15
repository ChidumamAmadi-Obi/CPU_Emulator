#pragma once

#include "config.hpp"

void inspectErrors(Assembler *assembler){ // list errors if any
    ProgramErrors error = assembler->errorCode;
    if (error != NONE) {
        SetConsoleTextAttribute(assembler->col, RED);
        printf("\n\nPROGRAM EXITED WITH ERROR CODE: %d\n", error);
        switch(error) {
            case LOADING_PROGRAM_ERROR: printf("ERROR LOADING PROGRAM FILE\n"); break;
            case EXPORTING_BINARY_ERROR: printf("ERROR EXPORTING BINARY FILE\n"); break;
            case SYNTAX_ERROR: printf("SYNTAX ERROR, '%s' IS AN INVALID TOKEN\n",assembler->program.invalidToken.c_str()); break;
            case SYMBOL_ERROR: printf("SYMBOL TABLE ERROR, LABEL '%s' IS UNDEFINED\n",assembler->program.invalidLabel.c_str()); break;
            case BIN_GEN_ERROR: printf("ERROR GENERATING BINARY FILE\n"); break;
            default: break;
        }
        SetConsoleTextAttribute(assembler->col, DEFAULT_WHITE);
    } else {
        SetConsoleTextAttribute(assembler->col, CYAN);
        printf("\nPROGRAM EXITED WITH ZERO ERRORS :]\n\n");
        SetConsoleTextAttribute(assembler->col, DEFAULT_WHITE);
    }
}
void inspectSymbolTable(Assembler *assembler){ // list all labels
    if (assembler->program.symbolTable.empty()) {
        SetConsoleTextAttribute(assembler->col, PINK);
        printf("\n========SYMBOL TABLE EMPTY========");
        SetConsoleTextAttribute(assembler->col, DEFAULT_WHITE);
    } else {
        SetConsoleTextAttribute(assembler->col, YELLOW);
        printf("\n===========SYMBOL TABLE===========\n");
        SetConsoleTextAttribute(assembler->col, DEFAULT_WHITE);
        for (auto i : assembler->program.symbolTable){
            printf(" LABEL: '%s' -> LOCATION: %d\n",i.first.c_str(), i.second);
        } 
        SetConsoleTextAttribute(assembler->col, YELLOW);
        printf("==================================");
        SetConsoleTextAttribute(assembler->col, DEFAULT_WHITE);
    } 
}
void inspectBinary(Assembler *assembler){ // print binary output in hex
    if (assembler->program.machineCode.empty()){
        SetConsoleTextAttribute(assembler->col, RED);
        printf("\n========NO BINARY GENERATED=======");
        SetConsoleTextAttribute(assembler->col, DEFAULT_WHITE);
    } else {
        SetConsoleTextAttribute(assembler->col, YELLOW);
        printf("\n===========BINARY OUTPUT==========\n");
        SetConsoleTextAttribute(assembler->col, DEFAULT_WHITE);
        for (int i=0; i<assembler->program.machineCode.size(); i++){
            printf(" 0x%x",assembler->program.machineCode[i]);
            if ((i+1)%8 == 0) printf("\n");
        }
        SetConsoleTextAttribute(assembler->col, YELLOW);
        printf("\n PROGRAM SIZE %d BYTES",assembler->program.sizeOfProgam);
        printf("\n==================================");
        SetConsoleTextAttribute(assembler->col, DEFAULT_WHITE);
    } 
}


