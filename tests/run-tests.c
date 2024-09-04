#include "types.h"
#include <libtest.h>
#include <stdio.h>


#define uwr_ptr(type, opt) ((type *)unwrap_opt(opt_usize_t, opt))

int main(void) {
    init_tests();

    hsmap_test_init();


    iter_c tests_iter = iter_tests();
    for_each(iter, tests_iter) {
        test_t *test = unwrap_opt(opt_vec_tests_t, iter);

        printf("\x1b[0;34;m( -> ) run test \x1b[1;m`%s`\x1b[0m from \x1b[1;m`%%s`\x1b[0m: ...",
                test->name);
        opt_ptr_c res = test->test();
        if (!res.is_some(res.self)) {
            printf("\x1b[3D\x1b[3;32m(ok) test succed.\x1b[0m\n");
            continue;
        }
        test_error_t err = unwrap_opt(opt_test_err_t, res);
        printf("\x1b[3D\x1b[3;31m(err) test failed; error:"
                "\n\t\t\x1b[0;31m\x1b[1m%s\x1b[0m\n", err.arguments);
    }

    return 0;
}
