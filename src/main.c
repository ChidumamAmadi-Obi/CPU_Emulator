#include "control_unit.h"
#include "cpu.h"

int main(void) { 
    initCPU(&cpu); // debugRAM(PRINT_PROGRAM_MODE,&cpu);

    static DecodedInst instructions; 
    while (cpu.isRunning){
        printf("%d \t",cpu.programCounter);
        runCPU(&cpu);
    }
    return 0;
}

