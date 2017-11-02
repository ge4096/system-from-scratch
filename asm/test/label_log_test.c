#include "label_log_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "label_log.h"
#include "test_common.h"

int label_log_test(void){
    int tests_failed = 0;
    printf("[%s:%d] Running %s\n", __FILE__, __LINE__, __func__);

    label_log_t label_log;
    init_label_log(&label_log);
    label_log_parameters_t label_log_parameters;
    TEST_ASSERT(read_last_entry_parameters(&label_log, &label_log_parameters)
                != 0);

    const uint32_t dummy_buffer_size = 2;
    uint8_t dummy_buffer[dummy_buffer_size];
    memset(dummy_buffer, 0, dummy_buffer_size);
    const uint32_t value = 0x1234;
    label_log_parameters.label_name = "a";
    label_log_parameters.memory_location = 0;
    label_log_parameters.bitmask = 0xFF;
    label_log_parameters.shift_amount = 0;
    register_label_log_entry(&label_log, &label_log_parameters);
    label_log_parameters.label_name = "b";
    label_log_parameters.memory_location = 1;
    label_log_parameters.bitmask = 0xFF00;
    label_log_parameters.shift_amount = 8;
    register_label_log_entry(&label_log, &label_log_parameters);
    TEST_ASSERT(read_last_entry_parameters(&label_log, &label_log_parameters)
                == 0);
    TEST_ASSERT(strcmp(label_log_parameters.label_name, "b") == 0);
    apply_last_label_log_entry(&label_log, value, dummy_buffer);
    TEST_ASSERT(dummy_buffer[1] == 0x12);
    remove_last_label_log_entry(&label_log);
    TEST_ASSERT(read_last_entry_parameters(&label_log, &label_log_parameters)
                == 0);
    TEST_ASSERT(strcmp(label_log_parameters.label_name, "a") == 0);
    apply_last_label_log_entry(&label_log, value, dummy_buffer);
    TEST_ASSERT(dummy_buffer[0] == 0x34);
    remove_last_label_log_entry(&label_log);

    free_label_log(&label_log);
    TEST_ASSERT(read_last_entry_parameters(&label_log, &label_log_parameters)
                != 0);

    return tests_failed;
}
