#include "debug.hpp"
#include "assembler.hpp"

int handleFilePaths(Assembler *assembler,int argc, char *argv[]);

int main(int argc, char *argv[]) { 
    Assembler assembler;
    int filePathErr = handleFilePaths(&assembler, argc, argv);

    if (filePathErr) return -1;

    assemble(&assembler);
    inspect(&assembler); // debug if needed
    
    return 0;
}

int handleFilePaths(Assembler *assembler,int argc, char *argv[]){
    if (argc > 1) {
        if (argc == 2) {
            printf("NO INPUT FILE SPECIFIED\n");
            return -1;
        } else if (argc > 3) {
            printf("TOO MANY ARGUMENTS\n");
            return -1;
        } else {
            assembler->programInputFilePath = argv[2];
            assembler->programOutputFilePath = argv[1];
        }
        return 0;
    }    
}