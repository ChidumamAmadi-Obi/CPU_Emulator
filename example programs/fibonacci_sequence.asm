;COMPUTES fib(8) = 21
;IN 47 CYCLES
LI r0 0;
LI r1 1; 
LI r2 7; loop count (0-7 is 8 loops)
LI r3 0; result

LOOP: 
    ADD r3 r0 r1;
    MOV r0 r1;
    MOV r1 r3;
    SUBI r2 r2 1; decriment counter
    JMP_ZRO END; if result is zero, jump to FINISH
    JMP LOOP; jump to LOOP

END: 
    STR 0xFE r3; store result in RAM location 0xFE
    HALT; end program
