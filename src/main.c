#include <stdio.h>

#include "ALU.h"

int main(void) {
    // testing alu
    int a = -127;
    int b = 10;
    ALUResults result = ALUEmulator(a,b,OP_SUB);

    printf("%d ,%d  \n", a, b);
    printf("RESULT: %d\n", result.output);
    printf("ZERO FLAG: %d\n", result.zeroFlag);
    printf("CARRY FLAG: %d \n", result.carryFlag);
    printf("OVERFLOW FLAG: %d\n", result.overflowFlag);
    printf("NEGATIVE FLAG: %d \n", result.negativeFlag);
    printf("ERROR FLAG: %d\n", result.errorFlag);
    return 0;
}