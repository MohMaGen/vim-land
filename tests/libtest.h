#pragma once

#include <types.h>


void init_tests(void);


typedef struct test_error {
    char *test_name;
    char *arguments;
    char *error;
} test_error_t;

opt_(tst_err, test_error_t);

typedef opt_ptr_c (*test_t)(void) ;

