#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

static inline int is_whitespace(char character){
    return ((character == ' ')  || (character == '\t') ||
            (character == '\n') || (character == '\r'));
}

static inline char to_lower(char character){
    if((character >= 'A') && (character <= 'Z')){
        return (char)((uint8_t)character - (uint8_t)('A' - 'a'));
    }
    else{
        return character;
    }
}

#endif
