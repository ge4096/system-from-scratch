#include "assembler.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "common.h"
#include "parser.h"
#include "types.h"

#define BUFFER_SIZE (1024)

#define ASSEMBLER_ERROR(format, ...) {                                        \
    printf("[%s:%d] " format "\n", in_file_name, line_number, ##__VA_ARGS__); \
    assembler_status.success = 1;                                             \
}

#define ADD_TO_BUFFER(character) {          \
    if(buffer_index >= BUFFER_SIZE){        \
        ASSEMBLER_ERROR("Buffer overflow"); \
    }                                       \
    else{                                   \
        buffer[buffer_index] = character;   \
        ++buffer_index;                     \
    }                                       \
}

#define ADD_TO_TOKENS {                                                       \
    if(line_tokens.num_tokens >= MAX_TOKENS_IN_LINE){                         \
        ASSEMBLER_ERROR("Too many tokens");                                   \
    }                                                                         \
    else{                                                                     \
        (line_tokens.tokens)[line_tokens.num_tokens] = buffer + buffer_index; \
        ++(line_tokens.num_tokens);                                           \
    }                                                                         \
}

#define PARSE_LINE {                                                  \
    buffer_index = 0;                                                 \
    parse_line(&line_tokens, &assembler_status);                      \
    if(assembler_status.parser_success != 0){                         \
        ASSEMBLER_ERROR("%s", assembler_status.parser_error_message); \
        assembler_status.parser_success = 0;                          \
    }                                                                 \
    clear_line_tokens(&line_tokens);                                  \
}

typedef enum {WHITESPACE, OPERATION_OR_LABEL, FIRST_OPERAND_SEPARATOR,
              LABEL_END, DEFINE_SEPARATOR, OPERAND, OPERAND_SEPARATOR,
              COMMENT_POSSIBLE_START, COMMENT,
              STRING, STRING_ESCAPE_FLAG, STRING_END} assembler_state_t;

int assemble(FILE * in_file, FILE * out_file, char * in_file_name){
    assembler_state_t last_state, current_state;
    char read_char;
    assembler_status_t assembler_status;
    line_tokens_t line_tokens;
    char * buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    uint32_t buffer_index;
    uint32_t line_number;
    
    init_parsers();
    clear_assembler_status(&assembler_status);
    last_state = WHITESPACE;
    buffer_index = 0;
    line_number = 0;
    while((read_char = (char)fgetc(in_file)) != EOF){
        if(read_char == '\n'){
            ++line_number;
        }

        switch(last_state){
            case WHITESPACE:
                if(read_char == '/'){
                    current_state = COMMENT_POSSIBLE_START;
                }
                else if(!is_whitespace(read_char)){
                    current_state = OPERATION_OR_LABEL;
                }
                break;
            case OPERATION_OR_LABEL:
                if(is_whitespace(read_char)){
                    current_state = FIRST_OPERAND_SEPARATOR;
                }
                else if(read_char == ':'){
                    current_state = LABEL_END;
                }
                break;
            case FIRST_OPERAND_SEPARATOR:
                if(read_char == '='){
                    current_state = DEFINE_SEPARATOR;
                }
                else if(read_char == '"'){
                    current_state = STRING;
                }
                else if(!is_whitespace(read_char)){
                    current_state = OPERAND;
                }
                break;
            case LABEL_END:
                if(read_char == '/'){
                    current_state = COMMENT_POSSIBLE_START;
                }
                else if(!is_whitespace(read_char)){
                    current_state = OPERATION_OR_LABEL;
                }
                else{
                    current_state = WHITESPACE;
                }
                break;
            case DEFINE_SEPARATOR:
                if(!is_whitespace(read_char)){
                    current_state = OPERAND;
                }
                break;
            case OPERAND:
                if(read_char == ';' || read_char == '\n'){
                    current_state = WHITESPACE;
                }
                else if(is_whitespace(read_char) || read_char == ','){
                    current_state = OPERAND_SEPARATOR;
                }
                break;
            case OPERAND_SEPARATOR:
                if(read_char == '/'){
                    current_state = COMMENT_POSSIBLE_START;
                }
                else if(read_char == '\n'){
                    current_state = WHITESPACE;
                }
                else if(!is_whitespace(read_char)){
                    current_state = OPERAND;
                }
                break;
            case COMMENT_POSSIBLE_START:
                if(read_char == '/'){
                    current_state = COMMENT;
                }
                else{
                    current_state = WHITESPACE;
                    ASSEMBLER_ERROR("Expected comment");
                }
                break;
            case COMMENT:
                if(read_char == '\n'){
                    current_state = WHITESPACE;
                }
                break;
            case STRING:
                if(read_char == '\\'){
                    current_state = STRING_ESCAPE_FLAG;
                }
                else if(read_char == '"'){
                    current_state = WHITESPACE;
                }
                break;
            case STRING_ESCAPE_FLAG:
                current_state = STRING;
                break;
            case STRING_END:
                if(read_char == ';' || read_char == '\n'){
                    current_state = WHITESPACE;
                }
                break;
        }

        switch(current_state){
            case WHITESPACE:
                if(buffer_index != 0){
                    ADD_TO_BUFFER('\0');
                    if(line_tokens.type != DEFINE){
                        line_tokens.type = INSTRUCTION;
                    }
                    PARSE_LINE;
                }
                break;
            case OPERATION_OR_LABEL:
                if(last_state != OPERATION_OR_LABEL){
                    ADD_TO_TOKENS;
                }
                ADD_TO_BUFFER(read_char);
                break;
            case FIRST_OPERAND_SEPARATOR:
                ADD_TO_BUFFER('\0');
                break;
            case LABEL_END:
                ADD_TO_BUFFER('\0');
                line_tokens.type = LABEL;
                PARSE_LINE;
                break;
            case DEFINE_SEPARATOR:
                line_tokens.type = DEFINE;
                break;
            case OPERAND:
                if(last_state != OPERAND){
                    ADD_TO_TOKENS;
                }
                ADD_TO_BUFFER(read_char);
                break;
            case OPERAND_SEPARATOR:
                if(last_state != OPERAND_SEPARATOR){
                    ADD_TO_BUFFER('\0');
                }
                break;
            case STRING:
                if(last_state == STRING_ESCAPE_FLAG){
                    switch(read_char){
                        case '"':
                            ADD_TO_BUFFER('"');
                            break;
                        case '\\':
                            ADD_TO_BUFFER('\\');
                            break;
                        case 'n':
                            ADD_TO_BUFFER('\n');
                            break;
                        case 't':
                            ADD_TO_BUFFER('\t');
                            break;
                        default:
                            break;
                    }
                }
                else if(last_state != STRING){
                    ADD_TO_TOKENS;
                }
                else{
                    ADD_TO_BUFFER(read_char);
                }
            default:
                break;
        }

        last_state = current_state;
    }

    if(buffer_index != 0){
        ADD_TO_BUFFER('\0');
        if(line_tokens.type != DEFINE){
            line_tokens.type = INSTRUCTION;
        }
        PARSE_LINE;
    }

    if(assembler_status.success == 0){
        fwrite(assembler_status.output_buffer, sizeof(uint8_t),
               assembler_status.memory_location, out_file);
    }

    free_assembler_status(&assembler_status);
    free_parsers();
    free(buffer);

    return assembler_status.success;
}
