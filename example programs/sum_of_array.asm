;SUMS ARRAY OF NUMNERS
;32 CYCLES

; Sum 4 numbers stored in RAM (sum = 71)
STR *0xF0 12;
STR *0xF1 12;
STR *0xF2 43;
STR *0xF3 4;

LD r0 0; sum = 0
LD r1 4; count = 4
LD r2 0xF0; pointer to array start

; start of loop (7)
LD r3 *r2; load array element
ADD r0 r0 r3; add to sum
ADD r2 r2 1; increment pointer
SUB r1 r1 1; decrement counter
JMP_ZRO 13; jump tp end
JMP 7; jump to start of loop

STR *0xFE r0;
HALT;