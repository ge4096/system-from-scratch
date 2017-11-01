#ifndef DIRECTIVE_PARSER_H
#define DIRECTIVE_PARSER_H

#include "types.h"

void init_directives(void);
void parse_directive(line_tokens_t * line_tokens,
                     assembler_status_t * assembler_status);
void free_directives(void);

#endif
