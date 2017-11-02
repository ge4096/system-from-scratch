#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdlib.h>

#include "definition_list.h"
#include "label_log.h"
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
    uint32_t line_number;
    uint8_t * output_buffer;
    uint32_t output_buffer_size;
    int parser_success;
    char * parser_error_message;
    definition_list_t * label_list;
    definition_list_t * define_list;
    label_log_t * label_log;
    int success;
} assembler_status_t;

static inline void
clear_assembler_status(assembler_status_t * assembler_status){
    assembler_status->memory_location = 0;
    assembler_status->line_number = 1;
    assembler_status->output_buffer = NULL;
    assembler_status->output_buffer_size = 0;
    assembler_status->parser_success = 0;
    assembler_status->success = 0;

    char * new_buffer;
    new_buffer = (char *)malloc(sizeof(char) * 256);
    assembler_status->parser_error_message = new_buffer;

    definition_list_t * new_list;
    new_list = (definition_list_t *)malloc(sizeof(definition_list_t));
    init_definition_list(new_list);
    assembler_status->label_list = new_list;
    new_list = (definition_list_t *)malloc(sizeof(definition_list_t));
    init_definition_list(new_list);
    assembler_status->define_list = new_list;

    label_log_t * new_label_log;
    new_label_log = (label_log_t *)malloc(sizeof(label_log_t));
    init_label_log(new_label_log);
    assembler_status->label_log = new_label_log;
}

void write_to_output_buffer(assembler_status_t * assembler_status,
                            uint8_t * bytes, uint32_t num_bytes);
void write_to_output_buffer_aligned(assembler_status_t * assembler_status,
                                    uint8_t * bytes, uint32_t num_bytes,
                                    uint32_t alignment);

static inline void
free_assembler_status(assembler_status_t * assembler_status){
    free_label_log(assembler_status->label_log);
    free(assembler_status->label_log);

    free_definition_list(assembler_status->label_list);
    free(assembler_status->label_list);
    free_definition_list(assembler_status->define_list);
    free(assembler_status->define_list);

    free(assembler_status->parser_error_message);

    if(assembler_status->output_buffer != NULL){
        free(assembler_status->output_buffer);
        assembler_status->output_buffer = NULL;
    }
}

#endif
