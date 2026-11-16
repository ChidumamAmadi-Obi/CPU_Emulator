#pragma once 

#include "config.h"
#include "alu.h"
#include "memory.h"

bool isInMemoryBounds(int memLocation, MemoryBoundsChecking loc);

void loadImmInst(CPU * cpu); // take literal number and store in register

void loadInst(CPU *cpu); // take thing from ram and store in reg

void storeInst(CPU *cpu); // take thing from reg and store in ram

void movInst(CPU *cpu); // copy value in one reg into another

void jumpInst(CPU*cpu); // overrite ram ptr, will jump to instruction in memory if condition is true

void arithmeticInst(CPU *cpu); // arithmetic and logical ops

