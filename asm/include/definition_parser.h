#ifndef DEFINITION_PARSER_H
#define DEFINITION_PARSER_H

#include "types.h"

void init_definitions(void);
void parse_label(line_tokens_t * line_tokens,
                 assembler_status_t * assembler_status);
void parse_define(line_tokens_t * line_tokens,
                  assembler_status_t * assembler_status);
void free_definitions(void);

#endif
