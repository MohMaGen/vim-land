#pragma once

#include <types.h>
#include <stdio.h>
#include <string.h>


void init_tests(void);


typedef struct test_error {
    char *arguments;
} test_error_t;

opt_(test_err, test_error_t);

typedef struct test { char *group; char *name; opt_ptr_c (*test)(void); } test_t;
vec_(tests, test_t);

void register_test(test_t);
iter_c iter_tests(void);

#define make_test_t(group, name) ((test_t) { #group, #name, &test_##name})

#define start_test(name)\
    opt_ptr_c test_##name(void) {\

#define end_test return none_opt_f32();\
    }

#define test_error(error) (alloc_opt_test_err((test_error_t) {error}))

#define assert_eq_str(must_be, actual) if (strcmp(must_be, actual) != 0) {\
        char *error = malloc(1024 * sizeof(char));\
        *error = '\0';\
        sprintf(error, "%s%d must be `%s`, but actual is `%s`.",  __FILE__, __LINE__, must_be, actual);\
        return test_error(error);\
    }

#define assert_eq_int(must_be, actual) if (must_be != actual) {\
        char *error = malloc(1024 * sizeof(char));\
        *error = '\0';\
        sprintf(error, "%s:%d must be `%d`, but actual is `%d`.", __FILE__, __LINE__, must_be, actual);\
        return test_error(error);\
    }
#define assert_pro(must_be, actual, eq, mst2str, act2str) if (eq(must_be, actual) == 0) {\
        char *error = malloc(1024 * sizeof(char)),\
            *mst_str = malloc(1024 * sizeof(char)),\
            *act_str = malloc(1024 * sizeof(char));\
        *error   = '\0';\
        *mst_str = '\0';\
        *act_str = '\0';\
        mst2str(mst_str, must_be);\
        act2str(act_str, actual);\
        sprintf(error, "%s%d must be `%s`, but actual is `%s`.",  __FILE__, __LINE__, mst_str, act_str);\
        free(act_str); free(mst_str);\
        return test_error(error);\
    }
\

#define assert_null(value) if (value != NULL) {\
        char *error = malloc(1024 * sizeof(char));\
        *error = '\0';\
        sprintf(error, "%s:%d value must be null, but it's: `%ld`.",\
                __FILE__, __LINE__, (unsigned long) value);\
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
void color_test_init(void);
