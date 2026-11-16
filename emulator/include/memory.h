#pragma once 

#include "config.h"

// RAM and ROM memory & program loading

void clearRAM(CPU* cpu); // clears data in ram but not read only memory

void loadProgram(CPU *cpu); // loads program from external txt file into read only memory


/* for reference 
https://www.youtube.com/watch?v=Ui6QyzcD3_E
https://www.tutorialkart.com/c-programming/how-to-read-binary-data-from-a-file-in-c/
*/
