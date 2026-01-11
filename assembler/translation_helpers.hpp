#pragma once

#include "config.hpp"

bool isLabel(string pastToken){// checks if token is an nudefined label. else returns false
    if((pastToken.compare("JMP") == 0 ||
        pastToken.compare("JMP_ABV") == 0 ||
        pastToken.compare("JMP_ZRO") == 0 ||
        pastToken.compare("JMP_OFW") == 0 ||
        pastToken.compare("JMP_NEG") == 0)){ return true;
    } return false;
}
bool isNumber(string token) { // checks if number is in desired format, else returns false
    if (token.empty()) return false;
    if (token.front() != '*') {
        if (token.size() > 2 && token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) {// hex prefix
            for (size_t i = 2; i < token.size(); i++) {
                if (!isxdigit(token[i])) return false;
            } return true;
        }
        
        if (token.size() > 1 && (token[0] == 'b' || token[0] == 'B')) {// bin prefix
            for (size_t i = 1; i < token.size(); i++) {
                if (token[i] != '0' && token[i] != '1') return false;
            } return true;
        }
       
        for (size_t i = 0; i < token.size(); i++) { // is decimal?
            if (!isdigit(token[i])) return false;
        } return true;
    } else if (token.front() == '*') { 
        if (token[1] == '0' && (token[2] == 'x' || token[2] == 'X')) {  // hex prefix
            for (size_t i=3; i < token.size(); i++) {
                if (!isxdigit(token[i])) return false;
            } return true;
        }
      
        if (token.size() > 1 && (token[1] == 'b' || token[2] == 'B')) {  // bin prefix
            for (size_t i = 2; i < token.size(); i++) {
                if (token[i] != '0' && token[i] != '1') return false;
            } return true;
        }
        
        for (size_t i = 1; i < token.size(); i++) { // is decimal?
            if (!isdigit(token[i])) return false;
        } return true;
    }
    return false;
}
int8_t handleInt(string token, Assembler *assembler){// handles binary and hex numbers
    if (token.front() =='*'){ // " * " symbolize memory locations in ram
        if ((token[1] == '0') && (token[2] == 'x','X')) {
            long decNumberLong = strtol(token.c_str()+1, NULL, 16);
            return (int8_t)decNumberLong;
        } else if (token[1] == 'b','B') {
            long decNumberLong = strtol(token.c_str()+2, NULL, 2);
            return (int8_t)decNumberLong;
        } else {
            long decNumberLong = strtol(token.c_str()+1, NULL, 10);
            return (int8_t)decNumberLong;
        }
    } else {
        if ((token.front() == '0') && (token[1] == 'x','X')) {
            long decNumberLong = strtol(token.c_str(), NULL, 16);
            return (int8_t)decNumberLong;
        } else if (token.front() == 'b','B') {
            long decNumberLong = strtol(token.c_str()+1, NULL, 2);
            return (int8_t)decNumberLong;
        } else { // just a normal number
            long decNumberLong = strtol(token.c_str(), NULL, 10);
            return (int8_t)decNumberLong;
        }
    }
}

void generateBin(Assembler *assembler){
    if(assembler->errorCode!=NONE) return;

    /*assembler->errorCode = BIN_GEN_ERROR;
    return;*/ 
}