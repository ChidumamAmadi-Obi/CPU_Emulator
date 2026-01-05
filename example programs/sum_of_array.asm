;SUMS ARRAY OF NUMNERS (sum = 71)
;32 CYCLES

; initialize array
STR *0xF0 12;
STR *0xF1 12;
STR *0xF2 43;
STR *0xF3 4;

LD r0 0; sum
LD r1 4; no of elements in array 
LD r2 0xF0; pointer to array start

; START: 7
LD r3 *r2; load array element with pointer
ADD r0 r0 r3; add to sum
ADD r2 r2 1; increment pointer
SUB r1 r1 1; decrement counter
JMP_ZRO 13; when the end of the array is reached, jump to FINISH
JMP 7; jump to START

; FINISH: 13
STR *0xFE r0; store result in RAM location 0xFE
HALT; end program