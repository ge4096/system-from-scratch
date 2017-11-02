#ifndef LABEL_LOG_H
#define LABEL_LOG_H

#include <stdint.h>
#include <stdlib.h>

typedef void * label_log_t;

typedef struct{
    char * label_name;
    uint32_t memory_location;
    uint32_t line_number;
    uint32_t bitmask;
    uint32_t shift_amount;
} label_log_parameters_t;

void register_label_log_entry(label_log_t * label_log,
                              label_log_parameters_t * label_log_parameters);
int read_last_entry_parameters(label_log_t * label_log,
                               label_log_parameters_t * label_log_parameters);
void apply_last_label_log_entry(label_log_t * label_log, uint32_t value, 
                                uint8_t * buffer);
void remove_last_label_log_entry(label_log_t * label_log);
void free_label_log(label_log_t * label_log);

static inline void init_label_log(label_log_t * label_log){
    *label_log = NULL;
}

#endif
