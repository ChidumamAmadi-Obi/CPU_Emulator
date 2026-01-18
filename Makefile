# HELP ______________________________________________________________________________
# make build <= only builds
# make run-only <= only runs both in order
# make run <= builds if needed then runs both in order

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
else 
CLEAN = rm $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)
endif

# directories
ASSEMBLER_DIR = assembler
EMULATOR_DIR = emulator

ASSEMBLER_SRC = $(wildcard $(ASSEMBLER_DIR)/src/*.cpp) # assembler source files
ASSEMBLER_INC = -I$(ASSEMBLER_DIR)/include

EMULATOR_SRC = $(wildcard $(EMULATOR_DIR)/src/*.c) # emulator source files
EMULATOR_INC = -I$(EMULATOR_DIR)/include

# executables
ASSEMBLER_EXEC = assembler_e
EMULATOR_EXEC = emulator_e

# _______________________________________________________________________________________ 
# default target, just build
all: $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)

$(ASSEMBLER_EXEC): $(ASSEMBLER_SRC) # build assembler
	$(CXX) $(ASSEMBLER_INC) -o $@ $(ASSEMBLER_SRC)

$(EMULATOR_EXEC): $(EMULATOR_SRC) # build emulator
	$(CC) $(EMULATOR_INC) -o $@ $(EMULATOR_SRC)

# build-only target 
build: $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)

# Run-only target (assumes exes already exist)
run-only:
	@echo "Running assembler..." 
	./$(ASSEMBLER_EXEC)
	@echo "Running emulator..."
	./$(EMULATOR_EXEC)

# build and run target (builds if needed, then runs)
run: $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)
	@echo "Running assembler..." 
	./$(ASSEMBLER_EXEC)
	@echo "Running emulator..."
	./$(EMULATOR_EXEC)

# remove exec files
clean:
	$(CLEAN)

.PHONY: all build run run-only clean


