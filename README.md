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

### Future Improvements
 - Simple Assembler Program (to support use of labels )
 - Support use of labels
 - State Operations
 - Better Handling of edge cases
 - Transition from 2D RAM to 1D


