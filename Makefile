CXX = g++
CC = gcc

ASSEMBLER_DIR = assembler # directories
EMULATOR_DIR = emulator

ASSEMBLER_SRC = $(wildcard $(ASSEMBLER_DIR)/src/*.cpp)# sssembler source files
ASSEMBLER_INC = -I$(ASSEMBLER_DIR)/include

EMULATOR_SRC = $(wildcard $(EMULATOR_DIR)/src/*.c)# emulator source files
EMULATOR_INC = -I$(EMULATOR_DIR)/include

ASSEMBLER_EXEC = assembler# executables
EMULATOR_EXEC = emulator

# _______________________________________________________________________________________ 
all: $(ASSEMBLER_EXEC) $(EMULATOR_EXEC) run# default target

$(ASSEMBLER_EXEC): $(ASSEMBLER_SRC)# build assembler
	$(CXX) $(ASSEMBLER_INC) -o $@ $(ASSEMBLER_SRC)

$(EMULATOR_EXEC): $(EMULATOR_SRC)# build emulator
	$(CC) $(EMULATOR_INC) -o $@ $(EMULATOR_SRC)

run: $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)# Run both programs MUST run assembler first to generate the binary file
	@echo "Running assembler..." 
	./$(ASSEMBLER_EXEC)
	@echo "Running emulator..."
	./$(EMULATOR_EXEC)

clean:# clean compiled files
	rm -f $(ASSEMBLER_EXEC) $(EMULATOR_EXEC)


.PHONY: all run clean

# IF YOU WANTED TO BUILD AND RUN MANUALLY ___________________________________________________________________
# g++ -Iassembler/include -o assembler assembler/src/*.cpp
# gcc -Iemulator/include -o emulator emulator/src/*.c  
# ./assembler
# ./emulator