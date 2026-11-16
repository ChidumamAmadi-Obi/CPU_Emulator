#pragma once 

#include "config.h"
#include <terminal_colors.h>

void showMetrics(CPU*cpu);
void showFatalErrors(CPU*cpu);
void inspectRam(CPU*cpu);
void inspectRegisters(CPU*cpu);
void inspectPC(CPU*cpu);
void inspectFlags(CPU*cpu);

void inspect(CPU*cpu);
