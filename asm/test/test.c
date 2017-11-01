#include <stdio.h>

#include "common_test.h"
#include "string_lookup_test.h"
#include "types_test.h"

static int run_tests(void){
    int tests_failed = 0;
    printf("[%s:%d] Starting unit tests\n", __FILE__, __LINE__);

    tests_failed += common_test();
    tests_failed += types_test();
    tests_failed += string_lookup_test();

    printf("[%s:%d] %d tests failed\n", __FILE__, __LINE__, tests_failed);
    return tests_failed;
}

int main(void){
    return run_tests();
}
