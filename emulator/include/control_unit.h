#pragma once

#include "config.h"
#include "ALU.h"
#include "memory.h"
#include "execute.h"

uint8_t numberOfArgs(CPU*cpu, uint8_t opcode); // return amount of operands to be expected in instruction
void initCtrlUnit(CPU *cpu); // initializes cpu registers and flags on start up
void cpuFetch(CPU *cpu);
void cpuDecodeExecute(CPU *cpu);