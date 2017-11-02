#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static inline int read_literal(char * literal, uint32_t * value){
    if(strcmp(literal, "0") == 0){
        *value = 0;
        return 0;
    }
    else if(sscanf(literal, "0x%x", (int *)value) != 0){
        return 0;
    }
    else if(sscanf(literal, "0%o", (int *)value) != 0){
        return 0;
    }
    else if(sscanf(literal, "%d", (int *)value) != 0){
        return 0;
    }
    else{
        return 1;
    }
}

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
