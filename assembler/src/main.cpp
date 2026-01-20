/*C-STYLE CPP FOR MULTIPLE-PASS ASSEMBLER

assembler takes assembly code from program.asm
and translates it into machine code that can be 
execeuted by the cpu emulator

in the first pass a symbol table is created to record and process all symbolic instructions
in the second pass the machine code is produced

load->tokenizer->first pass->second pass-> export machine code
*/ 

#include "debug_asm.hpp"
#include "assembler.hpp"

int main() { 
    Assembler assembler;
    assemble(&assembler);
    
    if (SHOW_SYMBOL_TABLE)      inspectSymbolTable(&assembler);
    if (SHOW_GENERATED_BINARY)  inspectBinary(&assembler);     
    if (SHOW_ERRORS)            inspectErrors(&assembler); 
    
    return 0;
}