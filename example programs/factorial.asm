;COMPUTES !5 = 120
;23 CYCLES

LD r0 5; calculate 5!
LD r1 1; temp

; LOOP: 2
MUL r1 r1 r0; multiply contents of r1 by r0
SUB r0 r0 1; decriment contents of r0
JMP_ZRO 6; if result is zero, end program
JMP 2; jump to LOOP

STR *0xFE r1; store result in RAM location 0xFE
HALT; end program