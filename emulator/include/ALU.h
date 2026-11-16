#pragma once

#include "config.h"

bool detectOverflow(int8_t inputA, int8_t inputB, ALUOperations operation, CPU* cpu); // detects overflow whith arithmetic ops

void clearFlags(CPU* cpu); // clears all alu status flags

void ALUEmulator(int8_t inputA, int8_t inputB, ALUOperations operation, CPU *cpu);