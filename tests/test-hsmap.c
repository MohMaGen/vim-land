#include "types.h"
#include <libtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

start_test(insert)
    srand(time(NULL));

    hsmap_strs_t strs_map = alloc_hsmap_strs(1);

    hsmap_strs_insert(&strs_map, "key", "value");
    assert_eq_str("value", *hsmap_strs_at(&strs_map, "key"))

    hsmap_strs_insert(&strs_map, "key", "new_value");
    assert_eq_str("new_value", *hsmap_strs_at(&strs_map, "key"))

    char *key_buf, *value_buf;
    for (int i = 0; i < 10000; i++) {
        key_buf = malloc(126 * sizeof(char));
        value_buf = malloc(126 * sizeof(char));

        int j;
        for (j = 0; j < 125; j++) {
            key_buf[j] = rand() % 50 + 30;
            value_buf[j] = rand() % 50 + 30;
        }
        key_buf[j] = '\0';
        value_buf[j] = '\0';

        hsmap_strs_insert(&strs_map, key_buf, value_buf);
        assert_eq_str(value_buf, *hsmap_strs_at(&strs_map, key_buf))

        value_buf[j] = 'b';
        value_buf[j+1] = '\0';
        hsmap_strs_insert(&strs_map, key_buf, value_buf);
        assert_eq_str(value_buf, *hsmap_strs_at(&strs_map, key_buf))

        free(value_buf);
        free(key_buf);
    }
    hsmap_strs_free(&strs_map);
end_test

hsmap_ints_pair_t *get_pairs(void);
hsmap_ints_pair_t *get_new_pairs(void);
start_test(append)
    hsmap_ints_t ints_map = alloc_hsmap_ints(1);
    hsmap_ints_append(&ints_map, get_pairs(), 100);


    for (int i = 1; i <= 100; i++) {
        int *res = hsmap_ints_at(&ints_map, i);
        assert_eq_int(i, *res);
    }

    hsmap_ints_append(&ints_map, get_new_pairs(), 100);
    for (int i = 1; i <= 100; i++) {
        int *res = hsmap_ints_at(&ints_map, i);
        assert_eq_int(i + 1, *res);
    }

    hsmap_ints_free(&ints_map);
end_test


start_test(remove)
    hsmap_ints_t ints_map = alloc_hsmap_ints(1);
    hsmap_ints_append(&ints_map, get_pairs(), 100);

    assert_eq_int(10, *hsmap_ints_at(&ints_map, 10))
    hsmap_ints_remove(&ints_map, 10);
    assert_null(hsmap_ints_at(&ints_map, 10))

    hsmap_ints_free(&ints_map);
end_test

void hsmap_test_init(void) {
    register_test(make_test_t(hsmap, insert));
    register_test(make_test_t(hsmap, append));
    register_test(make_test_t(hsmap, remove));
}

hsmap_ints_pair_t pairs[] = {
    (hsmap_ints_pair_t) { 1, 1 },
    (hsmap_ints_pair_t) { 2, 2 },
    (hsmap_ints_pair_t) { 3, 3 },
    (hsmap_ints_pair_t) { 4, 4 },
    (hsmap_ints_pair_t) { 5, 5 },
    (hsmap_ints_pair_t) { 6, 6 },
    (hsmap_ints_pair_t) { 7, 7 },
    (hsmap_ints_pair_t) { 8, 8 },
    (hsmap_ints_pair_t) { 9, 9 },
    (hsmap_ints_pair_t) { 10, 10 },
    (hsmap_ints_pair_t) { 11, 11 },
    (hsmap_ints_pair_t) { 12, 12 },
    (hsmap_ints_pair_t) { 13, 13 },
    (hsmap_ints_pair_t) { 14, 14 },
    (hsmap_ints_pair_t) { 15, 15 },
    (hsmap_ints_pair_t) { 16, 16 },
    (hsmap_ints_pair_t) { 17, 17 },
    (hsmap_ints_pair_t) { 18, 18 },
    (hsmap_ints_pair_t) { 19, 19 },
    (hsmap_ints_pair_t) { 20, 20 },
    (hsmap_ints_pair_t) { 21, 21 },
    (hsmap_ints_pair_t) { 22, 22 },
    (hsmap_ints_pair_t) { 23, 23 },
    (hsmap_ints_pair_t) { 24, 24 },
    (hsmap_ints_pair_t) { 25, 25 },
    (hsmap_ints_pair_t) { 26, 26 },
    (hsmap_ints_pair_t) { 27, 27 },
    (hsmap_ints_pair_t) { 28, 28 },
    (hsmap_ints_pair_t) { 29, 29 },
    (hsmap_ints_pair_t) { 30, 30 },
    (hsmap_ints_pair_t) { 31, 31 },
    (hsmap_ints_pair_t) { 32, 32 },
    (hsmap_ints_pair_t) { 33, 33 },
    (hsmap_ints_pair_t) { 34, 34 },
    (hsmap_ints_pair_t) { 35, 35 },
    (hsmap_ints_pair_t) { 36, 36 },
    (hsmap_ints_pair_t) { 37, 37 },
    (hsmap_ints_pair_t) { 38, 38 },
    (hsmap_ints_pair_t) { 39, 39 },
    (hsmap_ints_pair_t) { 40, 40 },
    (hsmap_ints_pair_t) { 41, 41 },
    (hsmap_ints_pair_t) { 42, 42 },
    (hsmap_ints_pair_t) { 43, 43 },
    (hsmap_ints_pair_t) { 44, 44 },
    (hsmap_ints_pair_t) { 45, 45 },
    (hsmap_ints_pair_t) { 46, 46 },
    (hsmap_ints_pair_t) { 47, 47 },
    (hsmap_ints_pair_t) { 48, 48 },
    (hsmap_ints_pair_t) { 49, 49 },
    (hsmap_ints_pair_t) { 50, 50 },
    (hsmap_ints_pair_t) { 51, 51 },
    (hsmap_ints_pair_t) { 52, 52 },
    (hsmap_ints_pair_t) { 53, 53 },
    (hsmap_ints_pair_t) { 54, 54 },
    (hsmap_ints_pair_t) { 55, 55 },
    (hsmap_ints_pair_t) { 56, 56 },
    (hsmap_ints_pair_t) { 57, 57 },
    (hsmap_ints_pair_t) { 58, 58 },
    (hsmap_ints_pair_t) { 59, 59 },
    (hsmap_ints_pair_t) { 60, 60 },
    (hsmap_ints_pair_t) { 61, 61 },
    (hsmap_ints_pair_t) { 62, 62 },
    (hsmap_ints_pair_t) { 63, 63 },
    (hsmap_ints_pair_t) { 64, 64 },
    (hsmap_ints_pair_t) { 65, 65 },
    (hsmap_ints_pair_t) { 66, 66 },
    (hsmap_ints_pair_t) { 67, 67 },
    (hsmap_ints_pair_t) { 68, 68 },
    (hsmap_ints_pair_t) { 69, 69 },
    (hsmap_ints_pair_t) { 70, 70 },
    (hsmap_ints_pair_t) { 71, 71 },
    (hsmap_ints_pair_t) { 72, 72 },
    (hsmap_ints_pair_t) { 73, 73 },
    (hsmap_ints_pair_t) { 74, 74 },
    (hsmap_ints_pair_t) { 75, 75 },
    (hsmap_ints_pair_t) { 76, 76 },
    (hsmap_ints_pair_t) { 77, 77 },
    (hsmap_ints_pair_t) { 78, 78 },
    (hsmap_ints_pair_t) { 79, 79 },
    (hsmap_ints_pair_t) { 80, 80 },
    (hsmap_ints_pair_t) { 81, 81 },
    (hsmap_ints_pair_t) { 82, 82 },
    (hsmap_ints_pair_t) { 83, 83 },
    (hsmap_ints_pair_t) { 84, 84 },
    (hsmap_ints_pair_t) { 85, 85 },
    (hsmap_ints_pair_t) { 86, 86 },
    (hsmap_ints_pair_t) { 87, 87 },
    (hsmap_ints_pair_t) { 88, 88 },
    (hsmap_ints_pair_t) { 89, 89 },
    (hsmap_ints_pair_t) { 90, 90 },
    (hsmap_ints_pair_t) { 91, 91 },
    (hsmap_ints_pair_t) { 92, 92 },
    (hsmap_ints_pair_t) { 93, 93 },
    (hsmap_ints_pair_t) { 94, 94 },
    (hsmap_ints_pair_t) { 95, 95 },
    (hsmap_ints_pair_t) { 96, 96 },
    (hsmap_ints_pair_t) { 97, 97 },
    (hsmap_ints_pair_t) { 98, 98 },
    (hsmap_ints_pair_t) { 99, 99 },
    (hsmap_ints_pair_t) { 100, 100 }
};

hsmap_ints_pair_t pairs_new[] = {
    (hsmap_ints_pair_t) { 1, 2 },
    (hsmap_ints_pair_t) { 2, 3 },
    (hsmap_ints_pair_t) { 3, 4 },
    (hsmap_ints_pair_t) { 4, 5 },
    (hsmap_ints_pair_t) { 5, 6 },
    (hsmap_ints_pair_t) { 6, 7 },
    (hsmap_ints_pair_t) { 7, 8 },
    (hsmap_ints_pair_t) { 8, 9 },
    (hsmap_ints_pair_t) { 9, 10 },
    (hsmap_ints_pair_t) { 10, 11 },
    (hsmap_ints_pair_t) { 11, 12 },
    (hsmap_ints_pair_t) { 12, 13 },
    (hsmap_ints_pair_t) { 13, 14 },
    (hsmap_ints_pair_t) { 14, 15 },
    (hsmap_ints_pair_t) { 15, 16 },
    (hsmap_ints_pair_t) { 16, 17 },
    (hsmap_ints_pair_t) { 17, 18 },
    (hsmap_ints_pair_t) { 18, 19 },
    (hsmap_ints_pair_t) { 19, 20 },
    (hsmap_ints_pair_t) { 20, 21 },
    (hsmap_ints_pair_t) { 21, 22 },
    (hsmap_ints_pair_t) { 22, 23 },
    (hsmap_ints_pair_t) { 23, 24 },
    (hsmap_ints_pair_t) { 24, 25 },
    (hsmap_ints_pair_t) { 25, 26 },
    (hsmap_ints_pair_t) { 26, 27 },
    (hsmap_ints_pair_t) { 27, 28 },
    (hsmap_ints_pair_t) { 28, 29 },
    (hsmap_ints_pair_t) { 29, 30 },
    (hsmap_ints_pair_t) { 30, 31 },
    (hsmap_ints_pair_t) { 31, 32 },
    (hsmap_ints_pair_t) { 32, 33 },
    (hsmap_ints_pair_t) { 33, 34 },
    (hsmap_ints_pair_t) { 34, 35 },
    (hsmap_ints_pair_t) { 35, 36 },
    (hsmap_ints_pair_t) { 36, 37 },
    (hsmap_ints_pair_t) { 37, 38 },
    (hsmap_ints_pair_t) { 38, 39 },
    (hsmap_ints_pair_t) { 39, 40 },
    (hsmap_ints_pair_t) { 40, 41 },
    (hsmap_ints_pair_t) { 41, 42 },
    (hsmap_ints_pair_t) { 42, 43 },
    (hsmap_ints_pair_t) { 43, 44 },
    (hsmap_ints_pair_t) { 44, 45 },
    (hsmap_ints_pair_t) { 45, 46 },
    (hsmap_ints_pair_t) { 46, 47 },
    (hsmap_ints_pair_t) { 47, 48 },
    (hsmap_ints_pair_t) { 48, 49 },
    (hsmap_ints_pair_t) { 49, 50 },
    (hsmap_ints_pair_t) { 50, 51 },
    (hsmap_ints_pair_t) { 51, 52 },
    (hsmap_ints_pair_t) { 52, 53 },
    (hsmap_ints_pair_t) { 53, 54 },
    (hsmap_ints_pair_t) { 54, 55 },
    (hsmap_ints_pair_t) { 55, 56 },
    (hsmap_ints_pair_t) { 56, 57 },
    (hsmap_ints_pair_t) { 57, 58 },
    (hsmap_ints_pair_t) { 58, 59 },
    (hsmap_ints_pair_t) { 59, 60 },
    (hsmap_ints_pair_t) { 60, 61 },
    (hsmap_ints_pair_t) { 61, 62 },
    (hsmap_ints_pair_t) { 62, 63 },
    (hsmap_ints_pair_t) { 63, 64 },
    (hsmap_ints_pair_t) { 64, 65 },
    (hsmap_ints_pair_t) { 65, 66 },
    (hsmap_ints_pair_t) { 66, 67 },
    (hsmap_ints_pair_t) { 67, 68 },
    (hsmap_ints_pair_t) { 68, 69 },
    (hsmap_ints_pair_t) { 69, 70 },
    (hsmap_ints_pair_t) { 70, 71 },
    (hsmap_ints_pair_t) { 71, 72 },
    (hsmap_ints_pair_t) { 72, 73 },
    (hsmap_ints_pair_t) { 73, 74 },
    (hsmap_ints_pair_t) { 74, 75 },
    (hsmap_ints_pair_t) { 75, 76 },
    (hsmap_ints_pair_t) { 76, 77 },
    (hsmap_ints_pair_t) { 77, 78 },
    (hsmap_ints_pair_t) { 78, 79 },
    (hsmap_ints_pair_t) { 79, 80 },
    (hsmap_ints_pair_t) { 80, 81 },
    (hsmap_ints_pair_t) { 81, 82 },
    (hsmap_ints_pair_t) { 82, 83 },
    (hsmap_ints_pair_t) { 83, 84 },
    (hsmap_ints_pair_t) { 84, 85 },
    (hsmap_ints_pair_t) { 85, 86 },
    (hsmap_ints_pair_t) { 86, 87 },
    (hsmap_ints_pair_t) { 87, 88 },
    (hsmap_ints_pair_t) { 88, 89 },
    (hsmap_ints_pair_t) { 89, 90 },
    (hsmap_ints_pair_t) { 90, 91 },
    (hsmap_ints_pair_t) { 91, 92 },
    (hsmap_ints_pair_t) { 92, 93 },
    (hsmap_ints_pair_t) { 93, 94 },
    (hsmap_ints_pair_t) { 94, 95 },
    (hsmap_ints_pair_t) { 95, 96 },
    (hsmap_ints_pair_t) { 96, 97 },
    (hsmap_ints_pair_t) { 97, 98 },
    (hsmap_ints_pair_t) { 98, 99 },
    (hsmap_ints_pair_t) { 99, 100 },
    (hsmap_ints_pair_t) { 100, 101 },
};


hsmap_ints_pair_t *get_pairs(void) { return pairs; }
hsmap_ints_pair_t *get_new_pairs(void) { return pairs_new; }
