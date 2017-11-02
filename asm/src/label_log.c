#include "label_log.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct label_log_entry_t{
    char * name;
    uint32_t location;
    uint32_t line_number;
    uint32_t bitmask;
    uint32_t shift_amount;
    struct label_log_entry_t * next;
} label_log_entry_t;

void register_label_log_entry(label_log_t * label_log, 
                              label_log_parameters_t * label_log_parameters){
    label_log_entry_t ** entry;
    label_log_entry_t * next_entry;

    entry = (label_log_entry_t **)label_log;
    next_entry = *entry;
    *entry = (label_log_entry_t *)malloc(sizeof(label_log_entry_t));
    (*entry)->name = (char *)malloc(sizeof(char) *
                                    (strlen(label_log_parameters->label_name)
                                     + 1));
    strcpy((*entry)->name, label_log_parameters->label_name);
    (*entry)->location = label_log_parameters->memory_location;
    (*entry)->line_number = label_log_parameters->line_number;
    (*entry)->bitmask = label_log_parameters->bitmask;
    (*entry)->shift_amount = label_log_parameters->shift_amount;
    (*entry)->next = next_entry;
}

int read_last_entry_parameters(label_log_t * label_log,
                               label_log_parameters_t * label_log_parameters){
    label_log_entry_t * entry = *((label_log_entry_t **)label_log);

    if(*label_log == NULL){
        return 1;
    }
    else{
        label_log_parameters->label_name = entry->name;
        label_log_parameters->memory_location = entry->location;
        label_log_parameters->line_number = entry->line_number;
        label_log_parameters->bitmask = entry->bitmask;
        label_log_parameters->shift_amount = entry->shift_amount;
        return 0;
    }
}

void apply_last_label_log_entry(label_log_t * label_log, uint32_t value,
                                uint8_t * buffer){
    label_log_entry_t * entry;
    uint8_t byte_value;

    entry = *((label_log_entry_t **)label_log);
    byte_value = (uint8_t)((value & entry->bitmask) >> entry->shift_amount);
    buffer[entry->location] |= byte_value;
}

void remove_last_label_log_entry(label_log_t * label_log){
    label_log_entry_t * entry;
    label_log_entry_t * next_entry;

    entry = *((label_log_entry_t **)label_log);
    if(entry != NULL){
        next_entry = entry->next;
        free(entry->name);
        free(entry);
        *label_log = (label_log_t)next_entry;
    }
}

void free_label_log(label_log_t * label_log){
    label_log_entry_t * entry;
    label_log_entry_t * next_entry;

    entry = *((label_log_entry_t **)label_log);
    while(entry != NULL){
        next_entry = entry->next;
        free(entry->name);
        free(entry);
        entry = next_entry;
    }

    *label_log = NULL;
}
