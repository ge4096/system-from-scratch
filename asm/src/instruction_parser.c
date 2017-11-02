#include "instruction_parser.h"

#include <stdio.h>

#include "string_lookup.h"
#include "types.h"

#define INSTRUCTION_ERROR(format, ...) {                                    \
    sprintf(assembler_status->parser_error_message, format, ##__VA_ARGS__); \
    assembler_status->parser_success = 1;                                   \
}

typedef enum {JMP} instruction_t;

static string_lookup_t instruction_lookup;

void init_instructions(void){
    init_string_lookup(&instruction_lookup);

    register_string_lookup_value(&instruction_lookup, "jmp", (int32_t)JMP);
}

void parse_instruction(line_tokens_t * line_tokens,
                       assembler_status_t * assembler_status){
    assembler_status->parser_success = 0;
    int32_t instruction_value = string_lookup_value(&instruction_lookup,
                                                    (line_tokens->tokens)[0]);
    if(instruction_value == DEFAULT_STRING_LOOKUP_VALUE){
        INSTRUCTION_ERROR("Unrecognized operation %s",
                          (line_tokens->tokens)[0]);
    }
    else{
        switch((instruction_t)instruction_value){
            case JMP:
                break;
        }
    }
}

void free_instructions(void){
    free_string_lookup(&instruction_lookup);
}
