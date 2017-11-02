#include "common_test.h"

#include <stdio.h>

#include "common.h"
#include "test_common.h"

int common_test(void){
    int tests_failed = 0;
    printf("[%s:%d] Running %s\n", __FILE__, __LINE__, __func__);

    uint32_t literal_value;
    TEST_ASSERT(read_literal("0", &literal_value) == 0);
    TEST_ASSERT(literal_value == 0);
    TEST_ASSERT(read_literal("42", &literal_value) == 0);
    TEST_ASSERT(literal_value == 42);
    TEST_ASSERT(read_literal("-42", &literal_value) == 0);
    TEST_ASSERT((int32_t)literal_value == -42);
    TEST_ASSERT(read_literal("042", &literal_value) == 0);
    TEST_ASSERT(literal_value == 042);
    TEST_ASSERT(read_literal("0x42", &literal_value) == 0);
    TEST_ASSERT(literal_value == 0x42);
    TEST_ASSERT(read_literal("a", &literal_value) != 0);

    TEST_ASSERT(is_whitespace(' ') != 0);
    TEST_ASSERT(is_whitespace('a') == 0);
    TEST_ASSERT(is_whitespace('\0') == 0);

    TEST_ASSERT(to_lower('A') == 'a');
    TEST_ASSERT(to_lower('a') == 'a');
    TEST_ASSERT(to_lower('1') == '1');

    return tests_failed;
}
