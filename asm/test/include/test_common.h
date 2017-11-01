#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <stdio.h>

#define TEST_ASSERT(condition) {                                  \
    if(!(condition)){                                             \
        printf("[%s:%d] Assertion failed\n", __FILE__, __LINE__); \
        tests_failed = 1;                                         \
    }                                                             \
}

#endif