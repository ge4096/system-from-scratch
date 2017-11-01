#ifndef PARSER_H
#define PARSER_H

#include "types.h"

void init_parsers(void);
void parse_line(line_tokens_t * line_tokens,
                assembler_status_t * assembler_status);
void free_parsers(void);

#endif
