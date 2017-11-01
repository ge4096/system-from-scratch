#include "types_test.h"

#include <stdio.h>
#include <stdlib.h>

#include "test_common.h"
#include "types.h"

int types_test(void){
    int tests_failed = 0;
    printf("[%s:%d] Running %s\n", __FILE__, __LINE__, __func__);

    assembler_status_t assembler_status;
    clear_assembler_status(&assembler_status);
    TEST_ASSERT(assembler_status.output_buffer == NULL);

    const uint32_t bytes_to_write = 5000;
    uint32_t byte_index;
    uint8_t byte = 0;
    for(byte_index = 0; byte_index < bytes_to_write; ++byte_index){
        write_to_output_buffer(&assembler_status, &byte, 1);
        byte = (uint8_t)(((uint32_t)byte + 1) % 256);
    }
    TEST_ASSERT((assembler_status.output_buffer)[0] == 0);
    TEST_ASSERT((assembler_status.output_buffer)[bytes_to_write - 1] ==
                (bytes_to_write - 1) % 256);

    free_assembler_status(&assembler_status);
    TEST_ASSERT(assembler_status.output_buffer == NULL);

    return tests_failed;
}
