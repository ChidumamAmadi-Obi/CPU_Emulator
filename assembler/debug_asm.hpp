#pragma once

#include "config.hpp"

void inspectErrors(Assembler *assembler){ // list errors if any
    ProgramErrors error = assembler->errorCode;
    printf("\n==================================");
    if (error != NONE) {
        printf("\nPROGRAM EXITED WITH ERROR CODE: %d\n", error);
        switch(error) {
            case FILE_ERROR: printf("ERROR OPENING PROGRAM FILE"); break;
            case SYNTAX_ERROR: printf("SYNTAX ERROR"); break;
            case SYMBOL_ERROR: printf("SYMBOL TABLE ERROR"); break;
            case BIN_GEN_ERROR: printf("ERROR GENERATING BINARY FILE"); break;
            default: break;
        }
    } else printf("\nPROGRAM EXITED WITH ZERO ERRORS :]");
    printf("\n==================================");
}

