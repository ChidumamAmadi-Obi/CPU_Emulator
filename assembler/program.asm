; for testing assembler only, cant run on cpu yet :[

; FACTORIAL EXAMPLE
LD r0 5; calculate 5!
LD r1 1; temp

LOOP:
    MUL r1 r1 r0; multiply contents of r1 by r0
    SUB r0 r0 1; decriment contents of r0
    JMP_ZRO LOOP; if result is zero, jump to END
    JMP END; jump to LOOP

END:
    STR *0xFE r1; store result in RAM location 0xFE

    HALT; end program
