# IF YOU WANTED TO BUILD AND RUN MANUALLY ___________________________________________
# g++ -Iassembler/include -o assembler assembler/src/*.cpp
# gcc -Iemulator/include -o emulator emulator/src/*.c  
# ./assembler
# ./emulator

CXX = g++
CC = gcc

# identify whih operating system user is on
ifeq ($(OS),Windows_NT)
	CLEAN = powershell -Command "Remove-Item -ErrorAction SilentlyContinue -Force $(ASSEMBLER_EXEC).exe, $(EMULATOR_EXEC).exe, *.obj, *.o, *.exe"
	CLEAN_ALL = powershell -Command "Remove-Item -ErrorAction SilentlyContinue -Force $(PROGRAM_BIN) $(ASSEMBLER_EXEC).exe, $(EMULATOR_EXEC).exe, *.obj, *.o, *.exe"
else 
	CLEAN = rm -f $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)
	CLEAN_ALL = rm -f $(PROGRAM_BIN) $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)
endif

# directories
ASSEMBLER_DIR = assembler
EMULATOR_DIR = emulator

ASSEMBLER_SRC = $(wildcard $(ASSEMBLER_DIR)/src/*.cpp) # assembler source files
ASSEMBLER_INC = -I$(ASSEMBLER_DIR)/include

EMULATOR_SRC = $(wildcard $(EMULATOR_DIR)/src/*.c) # emulator source files
EMULATOR_INC = -I$(EMULATOR_DIR)/include

CORE_INC = -Icominclude

# executables
ASSEMBLER_EXEC = assembler_e
EMULATOR_EXEC = emulator_e
PROGRAM_BIN = program.bin

help: #shows message
	@echo.
	@echo MAKEFILE TARGETS:
	@echo   all           - Builds both assembler and emulator
	@echo   run           - Builds if needed, then runs both programs
	@echo   run-emu       - Runs emulator separately for debugging
	@echo   run-assm      - Runs assembler separately for debugging
	@echo   clean         - Remove executable files
	@echo   clean-all     - Remove executable and binary files
	@echo   help          - Shows this help message
	@echo.
	@echo EXAMPLES:
	@echo   make run      - Build and run both programs
	@echo   make clean    - Clean up executables
	@echo.

all: $(ASSEMBLER_EXEC) $(EMULATOR_EXEC) 

	$(ASSEMBLER_EXEC): $(ASSEMBLER_SRC) # builds and runs assembler
		$(CXX) $(CORE_INC) $(ASSEMBLER_INC) -o $@ $(ASSEMBLER_SRC) 

	$(EMULATOR_EXEC): $(EMULATOR_SRC) # build and run emulator
		$(CC) $(CORE_INC) $(EMULATOR_INC) -o $@ $(EMULATOR_SRC)


run: $(ASSEMBLER_EXEC) $(EMULATOR_EXEC) # build and run target (builds if needed, then runs)
	@echo "Running assembler..." 
	./$(ASSEMBLER_EXEC)
	@echo "Running emulator..."
	./$(EMULATOR_EXEC)


run-emu: $(EMULATOR_EXEC) # run emulator separatly for debugging
	@echo "Running emulator..."
	./$(EMULATOR_EXEC)
run-assm: $(ASSEMBLER_EXEC) # run emulator separatly for debugging
	@echo "Running assembler..." 
	./$(ASSEMBLER_EXEC)


clean: # remove executable files
	$(CLEAN)
clean-all: # remove executable and binary files
	$(CLEAN_ALL)

.PHONY: all build run run-only clean
