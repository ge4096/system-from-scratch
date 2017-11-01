#ifndef STRING_LOOKUP_H
#define STRING_LOOKUP_H

#include <stdlib.h>

#define DEFAULT_STRING_LOOKUP_VALUE (-1)

typedef void * string_lookup_t;

void register_string_lookup_value(string_lookup_t * string_lookup, char * name,
                                  int32_t value);
int32_t string_lookup_value(string_lookup_t * string_lookup, char * name);
void free_string_lookup(string_lookup_t * string_lookup);

static inline void init_string_lookup(string_lookup_t * string_lookup){
    *string_lookup = NULL;
}

#endif
