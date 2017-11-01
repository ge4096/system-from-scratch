#include "parser.h"

#include <stdint.h>

#include "directive_parser.h"
#include "instruction_parser.h"
#include "types.h"

void init_parsers(void){
    init_instructions();
    init_directives();
}

#include <stdio.h>
void parse_line(line_tokens_t * line_tokens,
                assembler_status_t * assembler_status){
    uint32_t token_index;

    printf("type %d, %d args: ", line_tokens->type, line_tokens->num_tokens);
    for(token_index = 0; token_index < line_tokens->num_tokens; ++token_index){
        printf("%s", (line_tokens->tokens)[token_index]);
        if(token_index == (line_tokens->num_tokens - 1)){
            printf("\n");
        }
        else{
            printf(", ");
        }
    }
    if(line_tokens->num_tokens != 0){
        switch(line_tokens->type){
            case NONE:
                break;
            case LABEL:
                //parse_label(line_tokens, assembler_status);
                break;
            case DEFINE:
                //parse_define(line_tokens, assembler_status);
                break;
            case INSTRUCTION:
                if((line_tokens->tokens)[0][0] == '.'){
                    parse_directive(line_tokens, assembler_status);
                }
                else{
                    parse_instruction(line_tokens, assembler_status);
                }
                break;
        }
    }
}

void free_parsers(void){
    free_instructions();
    free_directives();
}
