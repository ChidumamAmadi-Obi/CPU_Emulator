# 8-Bit CPU Emulator in C
Lightweight, modular 8-bit CPU emulator with a multiple-pass assembler written in C/C++ for fun to explore computer architecture, instruction execution, and low-level programming.

### CPU Emulator & Assembler Demo
https://github.com/user-attachments/assets/75f93fe8-73d6-4d27-a5fe-8988b23c65bf

### Features 
**CPU Emulator**
 * Signed 8-bit arithmetic with overflow detection
 * Support for multiple number formats (decimal, hex, binary)
 * Program loading from external assembly file ```(program.asm)```
 * Configurable debug output (RAM view, PC tracing, error logging)

**Assembler**
  * Two-pass assembly process (symbol resolution, code generation)
  * Label support with forward referencing
  * Multiple number formats (decimal, hex, binary)
  * Pointer syntax (`*rX` for register-indirect)
  * Syntax validation with error location
  * Robust Error Reporting
  * Symbol table generation for debug visibility

### How to Run on Your Machine
   **1.** Clone Repo <br>
   **2.** Modify the file ```program.asm``` to run your own assembly instructions 
   **3.** Build and run CPU Emulator and Assembler 
   ``` bash
    g++ -Iassembler/include -o assembler assembler/src/*.cpp
    ./assembler
    gcc -Iemulator/include -o emulator emulator/src/*.c  
    ./emulator.exe
   ```
  
   #### Example ASM Program (Sum of Array)
   ``` asm
       ; EXAMPLE PROGRAM: SUMS ARRAY OF NUMNERS (sum = 76)
       ; EXECUTES IN 36 CYCLES
       
       ; initialize array
       LI r15 12; use temp register to load array values
       STR 0xF0 r15
       STR 0xF1 r15
       LI r15 48
       STR 0xF2 r15
       LI r15 4
       STR 0xF3 r15
       LI r15 0; clear r15
       
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
   ```
   ##### Assembler Output
   <img width="442" height="338" alt="image" src="https://github.com/user-attachments/assets/aa6cb01c-85df-4bb1-9c17-833e363499b9" /><br>
   ##### CPU Emulator Output 
   <img width="429" height="856" alt="image" src="https://github.com/user-attachments/assets/a85a3f0e-6d8f-45d5-a89c-8d258c495a71" />
   
### Preformance
- **_Fibonacci(8):_** 36 cycles, 21 result 
- **_5! Factorial:_** 23 cycles, 120 result  
- **_Sum of Array (4 elements):_** 36 cycles
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
 - [x] Modify Control Unit to decode & process binary instructions
 - [x] Transition from 2D RAM to 1D
 - [x] Better Handling of edge cases on the CPU emulator
 - [ ] Run Bubble sorting Algorithm on CPU
