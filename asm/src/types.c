#include "types.h"

#include <stdint.h>
#include <stdlib.h>

void write_to_output_buffer(assembler_status_t * assembler_status,
                            uint8_t * bytes, uint32_t num_bytes){
    uint8_t * new_buffer;
    if(assembler_status->output_buffer_size <
       (assembler_status->memory_location + num_bytes)){
        if(assembler_status->output_buffer_size == 0){
            assembler_status->output_buffer_size = 1024;
        }
        else{
            assembler_status->output_buffer_size *= 2;
        }
        new_buffer = realloc(assembler_status->output_buffer,
                             sizeof(uint8_t) *
                             assembler_status->output_buffer_size);
        if(new_buffer != NULL){
            assembler_status->output_buffer = new_buffer;
        }
    }

    uint32_t byte_index;
    uint8_t * buffer_pointer = assembler_status->output_buffer +
                               assembler_status->memory_location;
    for(byte_index = 0; byte_index < num_bytes; ++byte_index){
        buffer_pointer[byte_index] = bytes[byte_index];
    }
    assembler_status->memory_location += num_bytes;
}
