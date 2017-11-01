#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdlib.h>

#include "string_lookup.h"

#define MAX_TOKENS_IN_LINE (17)

typedef struct{
    enum {NONE, LABEL, DEFINE, INSTRUCTION} type;
    uint32_t num_tokens;
    char * tokens[MAX_TOKENS_IN_LINE];
} line_tokens_t;

static inline void clear_line_tokens(line_tokens_t * line_tokens){
    uint32_t token_index;
    line_tokens->type = NONE;
    line_tokens->num_tokens = 0;
    for(token_index = 0; token_index < MAX_TOKENS_IN_LINE; ++token_index){
        (line_tokens->tokens)[token_index] = NULL;
    }
}

typedef struct{
    uint32_t memory_location;
    uint8_t * output_buffer;
    uint32_t output_buffer_size;
    int parser_success;
    char * parser_error_message;
    int success;
} assembler_status_t;

static inline void
clear_assembler_status(assembler_status_t * assembler_status){
    assembler_status->memory_location = 0;
    assembler_status->output_buffer = NULL;
    assembler_status->output_buffer_size = 0;
    assembler_status->parser_success = 0;
    assembler_status->parser_error_message = NULL;
    assembler_status->success = 0;
}

void write_to_output_buffer(assembler_status_t * assembler_status,
                            uint8_t * bytes, uint32_t num_bytes);

static inline void
free_assembler_status(assembler_status_t * assembler_status){
    if(assembler_status->output_buffer != NULL){
        free(assembler_status->output_buffer);
        assembler_status->output_buffer = NULL;
    }
}

#endif
