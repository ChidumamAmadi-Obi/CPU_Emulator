; ===========================
; PUT CODE TO RUN ON CPU HERE
; ===========================

    LI r15 12; temp
    STR 0x01 0xFF r15
    JMP END
    NOP
    NOP
    NOP

END:
    HALT; end program