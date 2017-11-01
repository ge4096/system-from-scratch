#include "common_test.h"

#include <stdio.h>

#include "common.h"
#include "test_common.h"

int common_test(void){
    int tests_failed = 0;
    printf("[%s:%d] Running %s\n", __FILE__, __LINE__, __func__);

    TEST_ASSERT(is_whitespace(' ') != 0);
    TEST_ASSERT(is_whitespace('a') == 0);
    TEST_ASSERT(is_whitespace('\0') == 0);

    TEST_ASSERT(to_lower('A') == 'a');
    TEST_ASSERT(to_lower('a') == 'a');
    TEST_ASSERT(to_lower('1') == '1');

    return tests_failed;
}
