#include "control_unit.h"
#include "cpu.h"

int main(void) { 
    CPU cpu;
    initCPU(&cpu);

    while (cpu.isRunning) {
        runCPU(&cpu);
    } debugCPU(&cpu);

    return 0;
}