;COMPUTES fib(8) = 21
;47 CYCLES
LD r0, 0; 
LD r1, 1; 
LD r2, 7; 
LD r3, 0; 

ADD r3, r0, r1; 
MOV r0, r1; 
MOV r1, r3;
SUB r2, r2, 1; 
JMP_ZRO 10;
JMP 4;

STR *0xFE, r3; 
HALT;