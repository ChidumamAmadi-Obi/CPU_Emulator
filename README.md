# 8-Bit CPU Emulator in C
Lightweight, modular 8-bit CPU emulator written in C for fun to explore computer architecture, instruction execution, and low-level programming.

 * Full fetch-decode-execute pipeline
 * 16 general-purpose registers
 * 255 bytes of RAM (split into ROM and writable memory)
 * ALU suppoerting arithmetic and logic operations
 * Instruction set including load/store, jumps, arithmetic, and conditional branching
 * Configurable debugging woth compile-time flags
 * Support for *rX pointer syntax
 * Support for indirect addressing

### Features 
 * Signed 8-bit arithmetic with overflow detection
 * Support for multiple number formats (decimal, hex, binary)
 * Program loading from external assembly file ```(program.asm)```
 * Configurable debug output (RAM view, PC tracing, error logging)
 * Execution metrics

### Block Diagram
<img width="515" height="530" alt="image" src="https://github.com/user-attachments/assets/ec21b225-f742-4e39-9723-24ad19e1f3b4" />

### Example ASM Program (Factorial)
``` asm
; FACTORIAL EXAMPLE
LD r0 5; calculate 5!
LD r1 1; temp

; LOOP: 2
MUL r1 r1 r0; multiply contents of r1 by r0
SUB r0 r0 1; decriment contents of r0
JMP_ZRO 6; if result is zero, jump to END
JMP 2; jump to LOOP

; END: 6
STR *0xFE r1; store result in RAM location 0xFE
HALT; end program
```
#### Example Output Snippet
<img width="472" height="689" alt="image" src="https://github.com/user-attachments/assets/741980cd-d9d6-4c22-9b76-1f6c8b03d38c" />

### Preformance
- Fibonacci(8): 47 cycles, 21 result 
- 5! Factorial: 23 cycles, 120 result  
- Sum of Array (4 elements): 32 cycles
- Prime Number Checker (coming soon)
- Average CPI: 1 cycle per instruction

### Future Improvements
 - Simple Assembler Program
 - Support use of labels and macros
 - State Operations
 - Stack Operations
 - Better Handling of edge cases
 - Transition from 2D RAM to 1D
