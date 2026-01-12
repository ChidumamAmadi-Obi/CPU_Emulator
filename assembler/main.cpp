// C-STYLE CPP FOR MULTIPLE-PASS ASSEMBLER :]

#include "config.hpp"
#include "debug_asm.hpp"
#include "assembler.hpp"

int main() {

    Assembler assembler;
    assemble(&assembler);

    if (SHOW_ERRORS) inspectErrors(&assembler); 
    if (SHOW_SYMBOL_TABLE) inspectSymbolTable(&assembler);
    if (DEBUG_BIN_OUT) inspectBinary(&assembler);     

    return 0;
}