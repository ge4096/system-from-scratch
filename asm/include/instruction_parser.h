#ifndef INSTRUCTION_PARSER_H
#define INSTRUCTION_PARSER_H

#include "types.h"

void init_instructions(void);
void parse_instruction(line_tokens_t * line_tokens,
                       assembler_status_t * assembler_status);
void free_instructions(void);

#endif
