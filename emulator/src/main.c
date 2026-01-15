// #include "cpu.h"
#include "config.h"
#include "control_unit.h"
#include "cpu.h"

int main(void) { 
    clock_t start = clock();
    CPU cpu = {0}; 
    
    initCPU(&cpu);
    while (cpu.isRunning && cpu.fatalerror == NONE) {
        runCPU(&cpu);
    }

    clock_t end = clock();
    cpu.metrics.exetime = (double)(end - start) / CLOCKS_PER_SEC; // calculate execution time
    
    if (SHOW_RAM) inspectRam(&cpu);
    if (SHOW_REGISTERS) inspectRegisters(&cpu);
    if (SHOW_ERRORS) showFatalErrors(&cpu);

    printf("\nPROGRAM COMPLETED %d CYCLES IN %f SECONDS",cpu.metrics.cycles, cpu.metrics.exetime);
    return 0; 
}



/* PREFORMANCE
without assembler, string parsing: 
with assembler, binary: 
*/