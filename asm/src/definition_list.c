#include "definition_list.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct definition_list_entry_t{
    char * name;
    uint32_t value;
    struct definition_list_entry_t * next;
} definition_list_entry_t;

static definition_list_entry_t * create_definition_list_entry(uint32_t value){
    definition_list_entry_t * entry;

    entry = (definition_list_entry_t *)malloc(sizeof(definition_list_entry_t));
    entry->name = NULL;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

void register_definition_list_value(definition_list_t * definition_list,
                                    char * name, uint32_t value){
    definition_list_entry_t ** entry;
    definition_list_entry_t * next_entry;

    entry = (definition_list_entry_t **)definition_list;
    next_entry = *entry;
    *entry = create_definition_list_entry(value);
    (*entry)->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy((*entry)->name, name);
    (*entry)->next = next_entry;
}

int definition_list_value(definition_list_t * definition_list, char * name,
                          uint32_t * value){
    definition_list_entry_t * entry;

    entry = *((definition_list_entry_t **)definition_list);
    while(entry != NULL){
        if(strcmp(entry->name, name) == 0){
            if(value != NULL){
                *value = entry->value;
            }
            return 0;
        }
        entry = entry->next;
    }

    return 1;
}

void free_definition_list(definition_list_t * definition_list){
    definition_list_entry_t * entry;
    definition_list_entry_t * next_entry;

    entry = *((definition_list_entry_t **)definition_list);
    while(entry != NULL){
        next_entry = entry->next;
        free(entry->name);
        free(entry);
        entry = next_entry;
    }

    *definition_list = NULL;
}
