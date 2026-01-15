;COMPUTES !5 = 120
; in 23 CYCLES

LI r0 5; calculate 5!
LI r1 1; temp

LOOP: ; 6
    MUL r1 r1 r0; multiply contents of r1 by r0
    SUBI r0 r0 1; decriment contents of r0
    JMP_ZRO END; if result is zero, end program
    JMP LOOP; jump to LOOP

END: ; 18
    STR 0xFE r1; store result in RAM location 0xFE
    HALT; end program