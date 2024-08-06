#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

static int __test_passed = 0;
static int __test_failed = 0;

#include <stdio.h>

#define TEST_SUITE(suite_name) void TestSuite__ ## suite_name()

#define REGISTER_AND_RUN_SUITE(suite_name)                      \
    do {                                                        \
        printf("\e[1;32m===== %s =====\n\e[0m", #suite_name);   \
        TestSuite__ ## suite_name();                            \
        putchar('\n');                                          \
    } while(0)

#define TEST_CASE(description)                                          \
    for(int flag = printf("\e[0;32mRunning \'%s\' ... ", description), __passed = 1; \
        flag;                                                           \
        flag = 0,                                                       \
        __passed ? printf("PASS\n\e[0m") : 0, \
        __passed ? __test_passed++ : __test_failed++)

#define TEST_ASSERT(expression, error)                                  \
    if(!(expression)) {                                                 \
        fprintf(stdout, "\n\e[0;31m[%s, Ln: %d] Assertion failed: %s\n\tMessage: \'%s\'\n\e[0m", \
                __func__, __LINE__, #expression, error);                \
        __passed = 0;                                                   \
        continue;                                                       \
    }                                                                   \

#define TEST_PASSED_COUNT() (__test_passed)
#define TEST_FAILED_COUNT() (__test_failed)

#define PRINT_TEST_RESULT() printf("\n[Test passed: \e[0;32m%d\e[0m, Test Failed: \e[0;31m%d\e[0m]\n", __test_passed, __test_failed)

#endif
