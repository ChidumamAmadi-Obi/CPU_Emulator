;COMPUTES fib(8) = 21
;47 CYCLES
LD r0 0;
LD r1 1; 
LD r2 7; loop count (0-7 is 8 loops)
LD r3 0; result

; LOOP: 4
ADD r3 r0 r1;
MOV r0 r1;
MOV r1 r3;
SUB r2 r2 1; decriment counter
JMP_ZRO 10; if result is zero, jump to FINISH
JMP 4; jump to LOOP

; FINISH: 10
STR *0xFE r3; store result in RAM location 0xFE
HALT; end program