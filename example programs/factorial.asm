;COMPUTES !5 = 120
;23 CYCLES
LD r0 5; 
LD r1 1; 

MUL r1 r1 r0; 
SUB r0 r0 1; 
JMP_ZRO 6;
JMP 2;

STR *0x7D r1;
HALT;