#pragma once

// control color output by operating system

#ifdef _WIN32 
#include <windows.h>

// for colors on windows
#define COLOR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)
#define COLOR_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10)
#define COLOR_YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14)
#define COLOR_BOLD_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)    
#define COLOR_BOLD_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10) 
#define COLOR_BOLD_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15) 

#define COLOR_RESET SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7)

#else
// use ANSI excape codes if on mac/linux
#define COLOR_RED printf("\x1b[31m")
#define COLOR_GREEN printf("\x1b[32m")
#define COLOR_YELLOW printf("\x1b[33m")
#define COLOR_BOLD_RED printf("\x1b[1;31m")    
#define COLOR_BOLD_GREEN printf("\x1b[1;32m") 
#define COLOR_BOLD_WHITE printf("\x1b[1;37m") 
#define COLOR_RESET printf("\x1b[0m")

#endif
