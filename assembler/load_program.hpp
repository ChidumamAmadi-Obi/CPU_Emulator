#pragma once

#include "config.hpp"

void loadProgram(Assembler *assembler){ // loads program from external file and stores in string
    ifstream f("program.asm");

    if (!f.is_open()) {
        assembler->errorCode = FILE_ERROR;
        return;
    }

    string line;
    while (getline(f, line)) {
        // need to remove comments here before putting into string... 
        assembler->program.rawAsm+=(line + "\n");
    }

    if (DEBUG_RAW_ASM) printf("%s",assembler->program.rawAsm.c_str());
    f.close();
}