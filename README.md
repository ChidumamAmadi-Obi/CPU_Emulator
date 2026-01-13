# 8-Bit CPU Emulator in C
Lightweight, modular 8-bit CPU emulator with a multiple-pass assembler written in C/C++ for fun to explore computer architecture, instruction execution, and low-level programming.

### Assembler Demo
https://github.com/user-attachments/assets/024d12c7-3525-45a2-bc83-52e91714f8e2

### Features 
**CPU Emulator**
 * Signed 8-bit arithmetic with overflow detection
 * Support for multiple number formats (decimal, hex, binary)
 * Program loading from external assembly file ```(program.asm)```
 * Configurable debug output (RAM view, PC tracing, error logging)
 * Execution metrics

**Assembler (in progress)**
  * Two-pass assembly process (symbol resolution, code generation)
  * Label support with forward referencing
  * Multiple number formats (decimal, hex, binary)
  * Pointer syntax (`*rX` for register-indirect, `*0xFE` for absolute)
  * Syntax validation with error location
  * Robust Error Reporting
  * Symbol table generation for debug visibility

### Block Diagram
<img width="515" height="530" alt="image" src="https://github.com/user-attachments/assets/ec21b225-f742-4e39-9723-24ad19e1f3b4" />

### Instruction Set
| Instruction | Format | Description |
|-------------|--------|-------------|
| ADD | `ADD rd rs1 rs2` | Add two registers |
| SUB | `SUB rd rs1 rs2` | Subtract two registers |
| MUL | `MUL rd rs1 rs2` | Multiply two registers |
| AND | `AND rd rs1 rs2` | Logically AND two registers |
| OR | `OR rd rs1 rs2` | Logically OR two registers |
| XOR | `XOR rd rs1 rs2` | Logically XOR two registers |
| EQU | `EQU rd rs1 rs2` | Compare two registers |
| DIV | `DIV rd rs1 rs2` | Divide rs1 by rs2 |
| LD | `LD rd *addr` | Load from memory |
| STR | `STR *addr rs` | Store to memory |
| JMP | `JMP addr` | Unconditional jump |
| MOV | `MOV rs1 rs2` | Copy contents of register rs2 into rs1 |
| JMP_ZRO | `JMP_ZRO addr` | Jump if zero flag set |
| JMP_OFW | `JMP_OFW addr` | Jump if overflow flag set |
| JMP_NEG | `JMP_NEG addr` | Jump if negative flag set |
| JMP_ABV | `JMP_ABV addr` | Jump if both negative and zero flags are NOT set |

### How to Run on Your Machine
   **1.** Clone Repo and navigate to the emulator directory <br>
   **2.** Build and run with default program
   ``` bash
    gcc -Iinclude -o emulator src/main.c
    ./emulator.exe
   ```
   **3.** Modify ```program.asm``` to run your own assembly instructions 
   
   #### Example ASM Program (Factorial)
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
   ##### Example Output Snippet
   <img width="472" height="689" alt="image" src="https://github.com/user-attachments/assets/741980cd-d9d6-4c22-9b76-1f6c8b03d38c" />

### Preformance
- **_Fibonacci(8):_** 47 cycles, 21 result 
- **_5! Factorial:_** 23 cycles, 120 result  
- **_Sum of Array (4 elements):_** 32 cycles
- **_Prime Number Checker:_** (coming soon)
- **_Bubble Sort:_** (coming soon)
- **Average CPI:** 1 cycle per instruction

### Roadmaps
#### CPU Roadmap
- [x] Create ALU that handles signed arithmetic
- [x] Create RAM & ROM and load program
- [x] Create Control Unit
- [x] Can Execute Instructions
- [x] Track Preformance Metrics 
- [ ] State & Stack Operations
- [ ] Subroutine support

#### Assembler Roadmap
- [x] Load program
- [x] Impliment Tokenizer & Symbol Table
- [x] Impliment First Pass
- [x] Impliment Second Pass
- [x] Generate Binary File
- [ ] Macro support

#### Future Improvements
 - [ ] Modify Control Unit to decode & process binary instructions
 - [ ] Transition from 2D RAM to 1D
 - [ ] Run Bubble sorting Algorithm on CPU
 - [ ] Better Handling of edge cases
