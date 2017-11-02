#ifndef DEFINITION_LIST_H
#define DEFINITION_LIST_H

#include <stdint.h>
#include <stdlib.h>

typedef void * definition_list_t;

void register_definition_list_value(definition_list_t * definition_list,
                                    const char * name, uint32_t value);
int definition_list_value(definition_list_t * definition_list,
                          const char * name, uint32_t * value);
void free_definition_list(definition_list_t * definition_list);

static inline void init_definition_list(definition_list_t * definition_list){
    *definition_list = NULL;
}

#endif
