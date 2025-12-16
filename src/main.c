#include "cpu.h"

int main(void) { 
    CPU cpu = {0};
    initCPU(&cpu);
    while (cpu.isRunning) {
        runCPU(&cpu);
    } debugCPU(&cpu);

    printf("\nNumber of cycles: %d",cpu.metrics.cycles);
    debugRegisters(&cpu);
    return 0;
}