#include "control_unit.h"
#include "cpu.h"

int main(void) { // testing ld str and jmp ops
    CPU cpu;
    initCPU(&cpu);
    while (cpu.isRunning) runCPU(&cpu);
    debugCPU(&cpu);
}