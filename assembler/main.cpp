// C-STYLE CPP FOR MULTIPLE-PASS ASSEMBLER :]

#include "config.hpp"
#include "debug_asm.hpp"
#include "assembler.hpp"

int main() {
    Assembler assembler;
    assemble(&assembler);

    if (SHOW_ERRORS) inspectErrors(&assembler); 
    if (SHOW_SYMBOL_TABLE) inspectSymbolTable(&assembler);
    return 0;
}