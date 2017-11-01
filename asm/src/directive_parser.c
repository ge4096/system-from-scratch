#include "directive_parser.h"

#include <stdio.h>

#include "string_lookup.h"
#include "types.h"

typedef enum {ALIGN, DATA, STRING} directive_t;

static string_lookup_t directive_lookup;
static char * directive_error_message;

void init_directives(void){
    init_string_lookup(&directive_lookup);

    register_string_lookup_value(&directive_lookup, "align", (int32_t)ALIGN);
    register_string_lookup_value(&directive_lookup, "data", (int32_t)DATA);
    register_string_lookup_value(&directive_lookup, "string", (int32_t)STRING);

    directive_error_message = (char *)malloc(sizeof(char) * 256);
}

void parse_directive(line_tokens_t * line_tokens,
                     assembler_status_t * assembler_status){
    assembler_status->parser_success = 0;
    char * directive_lookup_start = (line_tokens->tokens)[0] + 1;
    int32_t directive_value = string_lookup_value(&directive_lookup,
                                                  directive_lookup_start);
    if(directive_value == DEFAULT_STRING_LOOKUP_VALUE){
        sprintf(directive_error_message, "Unrecognized directive %s",
                (line_tokens->tokens)[0]);
        assembler_status->parser_success = 1;
        assembler_status->parser_error_message = directive_error_message;
    }
    else{
        switch((directive_t)directive_value){
            case ALIGN:
                break;
            case DATA:
                break;
            case STRING:
                break;
        }
    }
}

void free_directives(void){
    free_string_lookup(&directive_lookup);
    free(directive_error_message);
}
