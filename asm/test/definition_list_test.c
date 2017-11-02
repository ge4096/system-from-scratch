#include "definition_list_test.h"

#include <stdio.h>

#include "definition_list.h"
#include "test_common.h"

int definition_list_test(void){
    int tests_failed = 0;
    printf("[%s:%d] Running %s\n", __FILE__, __LINE__, __func__);

    definition_list_t definition_list;
    init_definition_list(&definition_list);
    uint32_t value;

    value = 42;
    TEST_ASSERT(definition_list_value(&definition_list, "a", &value) != 0);
    TEST_ASSERT(value == 42);

    register_definition_list_value(&definition_list, "a", 0);
    register_definition_list_value(&definition_list, "aa", 1);
    register_definition_list_value(&definition_list, "ab", 2);
    register_definition_list_value(&definition_list, "1234567890_", 3);
    TEST_ASSERT(definition_list_value(&definition_list, "a", &value) == 0);
    TEST_ASSERT(value == 0);
    TEST_ASSERT(definition_list_value(&definition_list, "A", &value) != 0);
    TEST_ASSERT(definition_list_value(&definition_list, "aa", &value) == 0);
    TEST_ASSERT(value == 1);
    TEST_ASSERT(definition_list_value(&definition_list, "ab", &value) == 0);
    TEST_ASSERT(value == 2);
    TEST_ASSERT(definition_list_value(&definition_list, "ac", &value) != 0);
    TEST_ASSERT(definition_list_value(&definition_list, "1234567890_", &value)
                == 0);
    TEST_ASSERT(value == 3);

    free_definition_list(&definition_list);
    TEST_ASSERT(definition_list_value(&definition_list, "a", &value) != 0);

    return tests_failed;
}
