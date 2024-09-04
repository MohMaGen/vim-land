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

end_test


void hsmap_test_init(void) {
    register_test(make_test_t(insert));
}
