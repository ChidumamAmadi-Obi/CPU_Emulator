#include <stdio.h>

#include "ALU.h"
#include "registers.h"
#include "memory.h"

#include <string.h>

int main(void) {
    // testing ram and program loading
    memInit();
    loadProgram();
    debugRAM(PRINT_PROGRAM_MODE);
    return 0;
}

