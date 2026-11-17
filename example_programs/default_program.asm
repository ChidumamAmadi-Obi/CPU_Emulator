; ===========================
;     DEFAULT CPU PROGRAM
; ===========================

    LI r15 12; temp
    STR 0xFE r15
    JMP END
    NOP
    NOP
    NOP

END:
    HALT; end program