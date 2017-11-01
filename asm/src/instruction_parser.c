#include "instruction_parser.h"

#include <stdio.h>

#include "string_lookup.h"
#include "types.h"

typedef enum {JMP} instruction_t;

static string_lookup_t instruction_lookup;
static char * instruction_error_message;

void init_instructions(void){
    init_string_lookup(&instruction_lookup);

    register_string_lookup_value(&instruction_lookup, "jmp", (int32_t)JMP);

    instruction_error_message = (char *)malloc(sizeof(char) * 256);
}

void parse_instruction(line_tokens_t * line_tokens,
                       assembler_status_t * assembler_status){
    assembler_status->parser_success = 0;
    int32_t instruction_value = string_lookup_value(&instruction_lookup,
                                                    (line_tokens->tokens)[0]);
    if(instruction_value == DEFAULT_STRING_LOOKUP_VALUE){
        sprintf(instruction_error_message, "Unrecognized operation %s",
                (line_tokens->tokens)[0]);
        assembler_status->parser_success = 1;
        assembler_status->parser_error_message = instruction_error_message;
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
    free(instruction_error_message);
}
