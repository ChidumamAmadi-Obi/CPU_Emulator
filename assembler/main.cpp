// C-STYLE CPP FOR ASSEMBLER :]

#include "config.hpp"
#include "load_program.hpp"
#include "debug_asm.hpp"

int main() {
    Assembler assembler;
    loadProgram(&assembler);

    if (SHOW_ERRORS) inspectErrors(&assembler); 

    return 0;
}