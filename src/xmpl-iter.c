#include <stdio.h>
#include <string.h>
#include <types.h>

int even_int(opt_ptr_c v) {
    if (!v.is_some(v.self)) {
        return 0;
    }
    int value = *unwrap_opt(opt_array_iter_int_t, v);
    return ( value % 2 ) == 0;
}

int not_ten(opt_ptr_c v) {
    if (!v.is_some(v.self)) {
        return 0;
    }
    int value = *unwrap_opt(opt_array_iter_int_t, v);
    return value != 10;

}

opt_ptr_c mul_by_2(opt_ptr_c v) {
    int value = *unwrap_opt(opt_array_iter_int_t, v);
    return alloc_opt_int(value * 2);
}

opt_ptr_c to_a_rep(opt_ptr_c v) {
    int value = unwrap_opt(opt_int_t, v);
    char *a = malloc(value * sizeof(char));
    for (int i = 0; i < value; i++)
        a[i] = 'A';

    return alloc_opt_str(a);
}



int main() {
    char hello_world[] = "Hello, world!";

    iter_c iter = alloc_array_iter_char(hello_world, strlen(hello_world));
    for_each (curr, iter) {
        char *ptr = unwrap_opt(opt_array_iter_char_t, curr);
        printf("[%c] (%ld)\n", *ptr, (unsigned long)ptr);
    }
    free(iter.self);
    printf("\n");

    int values[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    iter = alloc_array_iter_int(values, 12);
    iter = filter(iter, even_int);
    iter = until(iter, not_ten);
    iter = map(iter, mul_by_2);
    iter = map(iter, to_a_rep);
    for_each (curr, iter) {
        char *ptr = unwrap_opt(opt_str_t, curr);
        printf("[%s]\n", ptr);
    }
    printf("\n");
    free(((filter_ptr_t*)iter.self)->data.self);
    free(iter.self);

    return 0;
}
