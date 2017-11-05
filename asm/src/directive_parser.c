#include "directive_parser.h"

#include <stdio.h>
#include <string.h>

#include "common.h"
#include "label_log.h"
#include "string_lookup.h"
#include "types.h"

#define DIRECTIVE_ERROR(format, ...) {                                      \
    sprintf(assembler_status->parser_error_message, format, ##__VA_ARGS__); \
    assembler_status->parser_success = 1;                                   \
}

typedef enum {ALIGN, BYTE, DATA, STRING, BLANK} directive_t;

static string_lookup_t directive_lookup;

void init_directives(void){
    init_string_lookup(&directive_lookup);

    register_string_lookup_value(&directive_lookup, "align", (int32_t)ALIGN);
    register_string_lookup_value(&directive_lookup, "byte", (int32_t)BYTE);
    register_string_lookup_value(&directive_lookup, "word", (int32_t)DATA);
    register_string_lookup_value(&directive_lookup, "data", (int32_t)DATA);
    register_string_lookup_value(&directive_lookup, "string", (int32_t)STRING);
    register_string_lookup_value(&directive_lookup, "blank", (int32_t)BLANK);
}

static void parse_align(line_tokens_t * line_tokens,
                        assembler_status_t * assembler_status){
    if(line_tokens->num_tokens != 2){
        DIRECTIVE_ERROR("Found %d operands for %s (expected 1)",
                        line_tokens->num_tokens - 1, (line_tokens->tokens)[0]);
        return;
    }

    uint32_t alignment_size;
    if((read_literal((line_tokens->tokens)[1], &alignment_size) != 0) &&
       (definition_list_value(assembler_status->define_list,
        (line_tokens->tokens)[1], &alignment_size) != 0)){
        DIRECTIVE_ERROR("Could not read operand %d to %s", 1,
                        (line_tokens->tokens)[0]);
        return;
    }
    if(alignment_size == 0){
        DIRECTIVE_ERROR("Alignment size cannot be zero");
        return;
    }
    if((int32_t)alignment_size < 0){
        DIRECTIVE_ERROR("Alignment size cannot be negative");
        return;
    }

    write_to_output_buffer_aligned(assembler_status, NULL, 0, alignment_size);
}

static void parse_byte(line_tokens_t * line_tokens,
                       assembler_status_t * assembler_status){
    uint32_t operand_index;
    uint32_t literal_value;
    uint8_t byte;

    for(operand_index = 1; operand_index < line_tokens->num_tokens;
        ++operand_index){
        if((read_literal((line_tokens->tokens)[operand_index], &literal_value)
            != 0) && (definition_list_value(assembler_status->define_list,
            (line_tokens->tokens)[operand_index], &literal_value) != 0)){
            DIRECTIVE_ERROR("Could not read operand %d to %s", operand_index,
                            (line_tokens->tokens)[0]);
            return;
        }
        byte = (uint8_t)literal_value;
        write_to_output_buffer(assembler_status, &byte, 1);
    }
}

static void parse_data(line_tokens_t * line_tokens,
                       assembler_status_t * assembler_status){
    uint32_t operand_index;
    uint32_t literal_value;
    label_log_parameters_t label_log_parameters;
    char * label_name;
    uint32_t base_memory_location;
    uint32_t byte_index;
    uint8_t byte;
    uint8_t literal_bytes[4];

    for(operand_index = 1; operand_index < line_tokens->num_tokens;
        ++operand_index){
        if((read_literal((line_tokens->tokens)[operand_index], &literal_value)
            != 0) && (definition_list_value(assembler_status->define_list,
            (line_tokens->tokens)[operand_index], &literal_value) != 0)){
            label_name = (line_tokens->tokens)[operand_index];
            label_log_parameters.label_name = label_name;
            label_log_parameters.line_number = assembler_status->line_number;
            base_memory_location = assembler_status->memory_location;
            for(byte_index = 0; byte_index < 4; ++byte_index){
                label_log_parameters.memory_location = base_memory_location +
                                                       byte_index;
                label_log_parameters.bitmask = (uint32_t)0xFF << byte_index;
                label_log_parameters.shift_amount = 8 * byte_index;
                register_label_log_entry(assembler_status->label_log,
                                         &label_log_parameters);
            }
            literal_value = 0;
        }
        for(byte_index = 0; byte_index < 4; ++byte_index){
            byte = (uint8_t)((literal_value & ((uint32_t)0xFF << 
                             (byte_index * 8))) >> (byte_index * 8));
            literal_bytes[byte_index] = byte;
        }
        write_to_output_buffer(assembler_status, literal_bytes, 4);
    }
}

static void parse_string(line_tokens_t * line_tokens,
                         assembler_status_t * assembler_status){
    if(line_tokens->num_tokens != 2){
        DIRECTIVE_ERROR("Found %d operands for %s (expected 1)",
                        line_tokens->num_tokens - 1, (line_tokens->tokens)[0]);
        return;
    }

    write_to_output_buffer(assembler_status,
                           (uint8_t *)(line_tokens->tokens)[1], 
                           (uint32_t)strlen((line_tokens->tokens)[1]) + 1);
}

static void parse_blank(line_tokens_t * line_tokens,
                         assembler_status_t * assembler_status){
    if(line_tokens->num_tokens != 2){
        DIRECTIVE_ERROR("Found %d operands for %s (expected 1)",
                        line_tokens->num_tokens - 1, (line_tokens->tokens)[0]);
        return;
    }

    uint32_t blank_bytes;
    if((read_literal((line_tokens->tokens)[1], &blank_bytes) != 0) &&
       (definition_list_value(assembler_status->define_list,
        (line_tokens->tokens)[1], &blank_bytes) != 0)){
        DIRECTIVE_ERROR("Could not read operand %d to %s", 1,
                        (line_tokens->tokens)[0]);
        return;
    }
    if((int32_t)blank_bytes < 0){
        DIRECTIVE_ERROR("Blank byte size cannot be negative");
        return;
    }

    uint8_t blank_byte = 0;
    uint32_t byte_index;
    for(byte_index = 0; byte_index < blank_bytes; ++byte_index){
        write_to_output_buffer(assembler_status, &blank_byte, 1);
    }
}

void parse_directive(line_tokens_t * line_tokens,
                     assembler_status_t * assembler_status){
    assembler_status->parser_success = 0;
    char * directive_lookup_start = (line_tokens->tokens)[0] + 1;
    int32_t directive_value = string_lookup_value(&directive_lookup,
                                                  directive_lookup_start);
    if(directive_value == DEFAULT_STRING_LOOKUP_VALUE){
        DIRECTIVE_ERROR("Unrecognized directive %s", (line_tokens->tokens)[0]);
    }
    else{
        switch((directive_t)directive_value){
            case ALIGN:
                parse_align(line_tokens, assembler_status);
                break;
            case BYTE:
                parse_byte(line_tokens, assembler_status);
                break;
            case DATA:
                parse_data(line_tokens, assembler_status);
                break;
            case STRING:
                parse_string(line_tokens, assembler_status);
                break;
            case BLANK:
                parse_blank(line_tokens, assembler_status);
                break;
        }
    }
}

void free_directives(void){
    free_string_lookup(&directive_lookup);
}
