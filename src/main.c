#include "control_unit.h"

DecodedInst instructions;

int main(void) { // testing ram and program loading
    memInit(&cpu); initCtrlUnit(&cpu);
    loadProgram(&cpu);
    // debugRAM(PRINT_PROGRAM_MODE,&cpu);

    // complete one cycle of fetch, decode execute
    cpuFetch(&cpu); 
    instructions = cpuDecode(&cpu);
    cpuExecute(&instructions,&cpu);

    printf("%d", cpu.gpRegs[0]);
    return 0;
}

