#include <libtest.h>
#include <stdio.h>


impl_opt_(test_err, test_error_t)
impl_vec_(tests, test_t)

vec_tests_t tests;

void init_tests(void) {
    printf("run tests\n");
    tests = alloc_vec_tests(1);
}


void register_test(test_t test) {
    vec_tests_push(&tests, test);
}

iter_c iter_tests(void) {
    return vec_tests_iter(&tests);
}
