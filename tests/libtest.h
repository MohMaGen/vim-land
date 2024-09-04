#pragma once

#include <types.h>
#include <stdio.h>
#include <string.h>


void init_tests(void);


typedef struct test_error {
    char *arguments;
} test_error_t;

opt_(test_err, test_error_t);

typedef struct test { char *name; opt_ptr_c (*test)(void); } test_t;
vec_(tests, test_t);

void register_test(test_t);
iter_c iter_tests(void);

#define make_test_t(name) ((test_t) { #name, &test_##name})

#define start_test(name)\
    opt_ptr_c test_##name(void) {\

#define end_test return none_opt_f32();\
    }

#define test_error(error) (alloc_opt_test_err((test_error_t) {error}))

#define assert_eq(must_be, actual) if (must_be != actual) {\
        char *error = malloc(1024 * sizeof(char));\
        *error = '\0';\
        sprintf(error, "must be `%s`, but actual is `%s`.", #must_be, #actual);\
        return test_error(error);\
    }
#define assert_eq_str(must_be, actual) if (strcmp(must_be, actual) != 0) {\
        char *error = malloc(1024 * sizeof(char));\
        *error = '\0';\
        sprintf(error, "must be `%s`, but actual is `%s`.", must_be, actual);\
        return test_error(error);\
    }

/*
*  _____ _____ ____ _____ ____
* |_   _| ____/ ___|_   _/ ___|
*   | | |  _| \___ \ | | \___ \
*   | | | |___ ___) || |  ___) |
*   |_| |_____|____/ |_| |____/
*/

void hsmap_test_init(void);
