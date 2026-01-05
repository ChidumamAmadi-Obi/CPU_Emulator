#include "cpu.h"

int main(void) { 
    CPU cpu = {0};
    initCPU(&cpu);
    while (cpu.isRunning) {
        runCPU(&cpu);
    } 
    
    printf("\n\nPROGRAM COMPLETED IN %d CYCLES",cpu.metrics.cycles);
    return 0;
}