#pragma once

#include "config.hpp"

void loadProgram(Assembler *assembler){ // loads program from external file and stores in string
    ifstream f("program.asm");
    
    if (!f.is_open()) {
        assembler->errorCode = LOADING_PROGRAM_ERROR;
        return;
    }

    string line="";

    if (!getline(f,line)) {
        assembler->errorCode = LOADING_PROGRAM_ERROR;
        return;
    }

    while (getline(f, line)) {
        size_t firstNonSpace = line.find_first_not_of(" \t"); 

        if (line.empty()) continue; // skip empty lines
        if (firstNonSpace != string::npos) line = line.substr(firstNonSpace);// rim leading whitespace
        else line.clear();
        
        size_t pos = line.find(';'); 

        if (pos != string::npos) line = line.substr(0, pos);// remove inline comments
        if (line.empty())  continue; // sip if line is empty after comment removal
        
        line.erase(line.find_last_not_of(' ') + 1); // trim trailing whitespace before puttin ginto string
        if (DEBUG_RAW_ASM) printf("%s\n", line.c_str());
        assembler->program.rawAsm += line + " ";
    }
    f.close();
}

void exportMachineCode(Assembler *assembler){
    if(assembler->errorCode!=NONE) return;

    ofstream binOut("program.bin",ios::binary);

    if (!binOut.is_open()) {
        assembler->errorCode = EXPORTING_BINARY_ERROR;
        return;
    } 

    for (int i=0; i<assembler->program.machineCode.size(); i++) {
        binOut.write((char*)&assembler->program.machineCode[i], sizeof(uint8_t));
    }

    binOut.flush();
    binOut.close();
}