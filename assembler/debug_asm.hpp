#pragma once

#include "config.hpp"

void inspectErrors(Assembler *assembler){ // list errors if any
    ProgramErrors error = assembler->errorCode;
    printf("\n==================================");
    if (error != NONE) {
        printf("\nPROGRAM EXITED WITH ERROR CODE: %d\n", error);
        switch(error) {
            case FILE_ERROR: printf("ERROR OPENING PROGRAM FILE"); break;
            case SYNTAX_ERROR: printf("SYNTAX ERROR, '%s' IS AN INVALID TOKEN",assembler->program.invalidToken.c_str()); break;
            case SYMBOL_ERROR: printf("SYMBOL TABLE ERROR"); break;
            case BIN_GEN_ERROR: printf("ERROR GENERATING BINARY FILE"); break;
            default: break;
        }
    } else printf("\nPROGRAM EXITED WITH ZERO ERRORS :]");
    printf("\n==================================");
}

void inspectSymbolTable(Assembler *assembler){ // list all labels
    printf("\n==================================\n");
    if (assembler->program.symbolTable.empty()) 
    printf("       SYMBOL TABLE EMPTY\n");
    for (auto i : assembler->program.symbolTable){
        printf("LABEL: '%s' -> LOCATION: %d\n",i.first.c_str(), i.second);
    }
    printf("==================================\n");
}

void inspectBinary(Assembler *assembler){ // print binary output

}

