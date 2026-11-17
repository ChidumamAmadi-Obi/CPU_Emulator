#include "debug.h"
#include "control_unit.h" 

int handleFilePath(CPU*cpu, int argc, char *argv[]);
void initCPU(CPU*cpu);
void runCPU(CPU*cpu);

int main(int argc, char *argv[]) { 
    clock_t start = clock();
    CPU cpu = {0}; 

    handleFilePath(&cpu, argc, argv);
    
    initCPU(&cpu);
    while (cpu.isRunning && cpu.fatalError == NONE) {
        runCPU(&cpu);
    }

    clock_t end = clock();
    cpu.metrics.exetime = (double)(end - start) / CLOCKS_PER_SEC; // calculate execution time

    inspect(&cpu); // deubg if needed
    
    return 0; 
}

int handleFilePath(CPU*cpu, int argc, char *argv[]){
    if (argc) {
        if (argc > 2) { 
            printf("TOO MANY ARGUMENTS");
            return -1;
        } else cpu->binFilePath = argv[1];
    } else { 
        cpu->binFilePath = "program.bin"; 
    }
    return 0;
}
void initCPU(CPU*cpu) {
    #ifdef SHOW_PC 
        COLOR_YELLOW; printf("\n=CYCLE==PC====OPCODE=======OPERANDS======="); COLOR_RESET;
    #endif

    initCtrlUnit(cpu); // sets and inittializes default flags of cpu
    loadProgram(cpu); // loads machine code from external file and puts into rom
}
void runCPU(CPU*cpu) { // fetch decode and execute pipeline
    cpuFetch(cpu); // loads next instruction from rom into instruction register
    cpu->metrics.cycles++;    
    cpuDecodeExecute(cpu); 
    #ifdef SHOW_PC
        inspectPC(cpu);
    #endif
}