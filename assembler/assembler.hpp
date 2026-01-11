#pragma once

#include "config.hpp"
#include "load_program.hpp"
#include "translation_helpers.hpp"

//_________________________________________________________________________________________________

void tokenize(Assembler *assembler){ // splits program up into individual "tokens" and stores into vector
    if(assembler->errorCode!=NONE) return; // exit if error
    stringstream check1(assembler->program.rawAsm);
    string intermediate;

    while(getline(check1, intermediate, ' ')) {
        assembler->program.tokens.push_back(intermediate);
    }

    if (DEBUG_TOKENIZER) {
        for (int i=0; i<assembler->program.tokens.size(); i++){
            printf("%s,",assembler->program.tokens[i].c_str());
        }
    }
}
void passOne(Assembler *assembler) { // check syntax and get labels w their location counters
    Maps compareMaps;
    uint8_t locationCounter=0;
    string token;
    string pastToken ="";
    bool printOut=false;
    bool gSyntax=false; // keeps track of correct syntax

    if(assembler->errorCode!=NONE) return;
    if (DEBUG_FIRST_PASS) printOut=true;
    for (int i=0; i<assembler->program.tokens.size(); i++){
        gSyntax=false; 
        token=assembler->program.tokens[i];
        if (printOut) printf("\n%d -> %s IS BEING PASSED...",locationCounter, token.c_str());
        
        if (compareMaps.mnemonicMap.find(token) != compareMaps.mnemonicMap.end()) { // if mnemonic
            locationCounter++;
            gSyntax=true;

        } else if (compareMaps.regMap.find(token) != compareMaps.regMap.end()){ // if reg number
            gSyntax=true;

        } else if (isNumber(token) )  { // check if its a literal number
            gSyntax=true; 

        } else if (token.back() == ':') { // check if its a label
            string labelName = token.substr(0, token.size() - 1);// Check if label name is reserved
            
            if (compareMaps.mnemonicMap.find(labelName) != compareMaps.mnemonicMap.end() ||
                compareMaps.regMap.find(labelName) != compareMaps.regMap.end()) {
                assembler->errorCode = SYNTAX_ERROR;
                return;
            }

            gSyntax=true;
            token.pop_back(); // remove ':' before storing
            assembler->program.symbolTable[token]=locationCounter; // put label into symbol tabel w location counter

        } else if (assembler->program.symbolTable.find(token) != assembler->program.symbolTable.end()){
            gSyntax=true; // if label has been defined in symbol table

        } else if (isLabel(pastToken)) {// if undefined label, will check if label actually exists in second pass
            gSyntax=true; 

        }
        
        if (!gSyntax) {
            assembler->errorCode=SYNTAX_ERROR;
            assembler->program.invalidToken=token;
            return;
        }
        if (printOut)printf("OK");
        pastToken=token;
    }
}
void passTwo(Assembler *assembler){
   if(assembler->errorCode!=NONE) return;

    /*
    1 map mnemonics to opcodes and operands
    2 replace labels w addresses from symbol tables
    3 gen binary out
    4 write bin to file
    */
}

void assemble(Assembler *assembler){ // runs assembler
    loadProgram(assembler);
    tokenize(assembler);
    
    passOne(assembler);
    //passTwo(assembler);
    
    // everything else blah blah
    /*
    for every assembling process
    functions should check for errorrs
    if there is an error the process should not
    go ahead, instead end the program

    eg.

    void tokenize(){
        if (error) return;
        //rest of code here
    }
    */
}
