#include "debug.hpp"
#include "assembler.hpp"

int main() { 
    Assembler assembler;
    assemble(&assembler);

    inspect(&assembler); // debug if needed
    
    return 0;
}