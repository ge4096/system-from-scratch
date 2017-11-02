#include "definition_parser.h"

#include <stdio.h>

#include "common.h"
#include "definition_list.h"
#include "types.h"

#define DEFINITION_ERROR(format, ...) {                                      \
    sprintf(assembler_status->parser_error_message, format, ##__VA_ARGS__); \
    assembler_status->parser_success = 1;                                   \
}

void init_definitions(void){
    return;
}

void parse_label(line_tokens_t * line_tokens,
                 assembler_status_t * assembler_status){
    assembler_status->parser_success = 0;

    if(line_tokens->num_tokens != 1){
        DEFINITION_ERROR("Found %d operands for %s label (expected 0)",
                         line_tokens->num_tokens - 1,
                         (line_tokens->tokens)[0]);
        return;
    }

    if(definition_list_value(assembler_status->label_list,
                             (line_tokens->tokens)[0], NULL) == 0){
        DEFINITION_ERROR("Label %s already exists", (line_tokens->tokens)[0]);
        return;
    }

    register_definition_list_value(assembler_status->label_list,
                                   (line_tokens->tokens)[0],
                                   assembler_status->memory_location);
}

void parse_define(line_tokens_t * line_tokens,
                  assembler_status_t * assembler_status){
    assembler_status->parser_success = 0;

    if(line_tokens->num_tokens != 2){
        DEFINITION_ERROR("Found %d operands for %s define (expected 1)",
                         line_tokens->num_tokens - 1,
                         (line_tokens->tokens)[0]);
        return;
    }

    uint32_t value;
    if((read_literal((line_tokens->tokens)[1], &value) != 0) &&
       (definition_list_value(assembler_status->define_list,
        (line_tokens->tokens)[1], &value) != 0)){
        DEFINITION_ERROR("Could not read operand %d to %s define", 1,
                         (line_tokens->tokens)[0]);
        return;
    }

    register_definition_list_value(assembler_status->define_list,
                                   (line_tokens->tokens)[0], value);
}

void free_definitions(void){
    return;
}
