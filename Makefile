# IF YOU WANTED TO BUILD AND RUN MANUALLY ___________________________________________
# g++ -Iassembler/include -o assembler assembler/src/*.cpp
# gcc -Iemulator/include -o emulator emulator/src/*.c  
# ./assembler
# ./emulator

CXX = g++
CC = gcc

# use -D to pass macro definitions into c/cpp files
# default debug flags...
EMULATOR_DEBUG_FLAGS ?= -DSHOW_ERRORS=1 \
						-DSHOW_REGISTERS=1 \
						-DSHOW_PC=1 \
						-DSHOW_METRICS=1 \
						-DSHOW_RAM=0 \
						-DSHOW_FLAGS=0

ASSEMBLER_DEBUG_FLAGS ?= -DSHOW_ERRORS=1 \
  						 -DSHOW_SYMBOL_TABLE=1 \
						 -DSHOW_GENERATED_BINARY=1 \
						 -DDEBUG_RAW_ASM=0 \
						 -DDEBUG_TOKENIZER=0 \
						 -DDEBUG_FIRST_PASS=0 \
						 -DDEBUG_SECOND_PASS=0

# identify which operating system user is on
ifeq ($(OS),Windows_NT)
	CLEAN = powershell -Command "Remove-Item -ErrorAction SilentlyContinue -Force $(ASSEMBLER_EXEC).exe, $(EMULATOR_EXEC).exe"
	CLEAN_ALL = powershell -Command "Remove-Item -ErrorAction SilentlyContinue -Force $(PROGRAM_BIN).bin $(ASSEMBLER_EXEC).exe, $(EMULATOR_EXEC).exe"
	CLEAN-BIN = powershell -Command "Remove-Item -ErrorAction SilentlyContinue -Force $(PROGRAM_BIN).bin"
else 
	CLEAN = rm -f $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)
	CLEAN_ALL = rm -f $(PROGRAM_BIN) $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)
	CLEAN-BIN = rm -f $(PROGRAM_BIN)
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
PROGRAM_BIN = program

# Rules
$(ASSEMBLER_EXEC): $(ASSEMBLER_SRC) 
	$(CXX) $(ASSEMBLER_DEBUG_FLAGS) $(CORE_INC) $(ASSEMBLER_INC) -o $@ $(ASSEMBLER_SRC)

$(EMULATOR_EXEC): $(EMULATOR_SRC)
	$(CC) $(EMULATOR_DEBUG_FLAGS) $(CORE_INC) $(EMULATOR_INC) -o $@ $(EMULATOR_SRC)

help: # shows message
	@echo.
	@echo MAKEFILE TARGETS:
	@echo   all           "Builds both assembler and emulator"
	@echo   run           "Builds if needed, then runs both programs"
	@echo   run-emu       "Runs emulator separately for debugging"
	@echo   run-assm      "Runs assembler separately for debugging"
	@echo   clean         "Remove executable files"
	@echo   clean-bin     "Remove bin file generated from assembler only"
	@echo   clean-all     "Remove executable and binary files"
	@echo   help          "Shows this help message"
	@echo.
	@echo EXAMPLES:
	@echo   make run      "Build and run both programs"
	@echo   make clean    "Clean up executables"
	@echo.
	@echo.
	@echo COMPILE TIME DEBUG FLAGS:
	@echo   assembler     -DSHOW_ERRORS
	@echo                 -DSHOW_SYMBOL_TABLE
	@echo                 -DSHOW_GENERATED_BINARY
	@echo                 -DDEBUG_RAW_ASM
	@echo                 -DDEBUG_TOKENIZER
	@echo                 -DDEBUG_FIRST_PASS 
	@echo                 -DDEBUG_SECOND_PASS
	@echo 	emulator      -DSHOW_ERRORS
	@echo                 -DSHOW_RAM
	@echo                 -DSHOW_REGISTERS
	@echo                 -DSHOW_FLAGS
	@echo                 -DSHOW_PC
	@echo                 -SHOW_METRICS
	@echo
	@echo EXAMPLES
	@echo   make run EMULATOR_DEBUG_FLAGS=-DSHOW_ERRORS=1 ASSEMBLER_DEBUG_FLAGS=-DSHOW_ERRORS
	@echo   "ONLY enables errors reporting for emulator and assembler"
	@echo.

all: $(ASSEMBLER_EXEC) $(EMULATOR_EXEC) 
build: all
run: $(ASSEMBLER_EXEC) $(EMULATOR_EXEC) # build and run target (builds if needed, then runs)
	@echo "Running assembler..." 
	./$(ASSEMBLER_EXEC)
	@echo "Running emulator..."
	./$(EMULATOR_EXEC)

run-emu: $(EMULATOR_EXEC) # run emulator separately for debugging
	@echo "Running emulator..."
	./$(EMULATOR_EXEC)

run-assm: $(ASSEMBLER_EXEC) # run assembler separately for debugging
	@echo "Running assembler..." 
	./$(ASSEMBLER_EXEC)

clean: # remove executable files
	$(CLEAN)

clean-bin: # remove bin file generated from assembler only (program.bin)
	$(CLEAN-BIN)

clean-all: # remove executable and binary files
	$(CLEAN_ALL)

.PHONY: all build run run-emu run-assm clean clean-all help