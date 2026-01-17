#pragma once

// control color output by operating system

#ifdef _WIN32 // for colors on windows
#include <windows.h>

#define HANDLE GetStdHandle(STD_OUTPUT_HANDLE)

#define RED 4
#define GREEN 2
#define YELLOW 6
#define BRIGHT_RED 12
#define BRIGHT_GREEN 10
#define BRIGHT_YELLOW 14
#define BRIGHT_WHITE 15

#define COLOR_RED SetConsoleTextAttribute(HANDLE, RED)
#define COLOR_GREEN SetConsoleTextAttribute(HANDLE, GREEN)
#define COLOR_YELLOW SetConsoleTextAttribute(HANDLE, YELLOW)
#define COLOR_BOLD_RED SetConsoleTextAttribute(HANDLE, BRIGHT_RED)    
#define COLOR_BOLD_GREEN SetConsoleTextAttribute(HANDLE, BRIGHT_GREEN) 
#define COLOR_BOLD_YELLOW SetConsoleTextAttribute(HANDLE, BRIGHT_YELLOW) 
#define COLOR_BOLD_WHITE SetConsoleTextAttribute(HANDLE, BRIGHT_WHITE) 
#define COLOR_RESET SetConsoleTextAttribute(HANDLE,7)

#else
// use ANSI excape codes if on mac/linux
#define COLOR_RED printf("\x1b[31m")
#define COLOR_GREEN printf("\x1b[32m")
#define COLOR_YELLOW printf("\x1b[33m")
#define COLOR_BOLD_RED printf("\x1b[1;31m")    
#define COLOR_BOLD_GREEN printf("\x1b[1;32m") 
#define COLOR_BOLD_WHITE printf("\x1b[1;37m") 
#define COLOR_BOLD_YELLOW printf("\x1b[1;33m")
#define COLOR_RESET printf("\x1b[0m")

#endif
