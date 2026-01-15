; ===========================
; PUT CODE TO RUN ON CPU HERE
; ===========================

; EXAMPLE PROGRAM: SUMS ARRAY OF NUMNERS (sum = 76)
;36 CYCLES

; initialize array
LI r15 12; temp
STR 0xF0 r15
STR 0xF1 r15
LI r15 48
STR 0xF2 r15
LI r15 4
STR 0xF3 r15
LI r15 0; clear r0

LI r0 0; sum
LI r1 4; no of elements in array 
LI r2 0xF0; pointer to array start

START:
    LD r3 *r2; load array element with pointer
    ADD r0 r0 r3; add to sum
    ADDI r2 r2 1; increment pointer
    SUBI r1 r1 1; decrement counter
    JMP_ZRO FINISH; when the end of the array is reached, jump to FINISH
    JMP START; jump to START

FINISH:
    STR 0xFE r0; store result in RAM location 0xFE
    HALT; end program