#include "string_lookup_test.h"

#include <stdio.h>

#include "string_lookup.h"
#include "test_common.h"

int string_lookup_test(void){
    int tests_failed = 0;
    printf("[%s:%d] Running %s\n", __FILE__, __LINE__, __func__);

    string_lookup_t string_lookup;
    init_string_lookup(&string_lookup);

    TEST_ASSERT((void *)string_lookup == NULL);
    TEST_ASSERT(string_lookup_value(&string_lookup, "a") ==
                DEFAULT_STRING_LOOKUP_VALUE);

    register_string_lookup_value(&string_lookup, "a", 0);
    register_string_lookup_value(&string_lookup, "aa", 1);
    register_string_lookup_value(&string_lookup, "ab", 2);
    TEST_ASSERT((void *)string_lookup != NULL);
    TEST_ASSERT(string_lookup_value(&string_lookup, "a") == 0);
    TEST_ASSERT(string_lookup_value(&string_lookup, "A") == 0);
    TEST_ASSERT(string_lookup_value(&string_lookup, "aa") == 1);
    TEST_ASSERT(string_lookup_value(&string_lookup, "ab") == 2);
    TEST_ASSERT(string_lookup_value(&string_lookup, "ac") ==
                DEFAULT_STRING_LOOKUP_VALUE);

    free_string_lookup(&string_lookup);
    TEST_ASSERT((void *)string_lookup == NULL);
    TEST_ASSERT(string_lookup_value(&string_lookup, "a") ==
                DEFAULT_STRING_LOOKUP_VALUE);

    return tests_failed;
}
