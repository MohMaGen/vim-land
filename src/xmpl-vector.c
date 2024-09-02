#include <stdio.h>
#include <types.h>


int data[] = { 10, 20, 30, 40 };

#define print_vec(){\
        iter_c iter = vec_int_iter(&vec);\
        printf("\n{ len: %ld, capacity: %ld }\n\n", vec.len, vec.capacity);\
        for_each (i, iter) {\
          int *it = unwrap_opt(opt_vec_int_t, i);\
          printf("[%d] (%ld)\n", *it, (unsigned long)it);\
        }\
    }

int main(void) {
    vec_int_t vec = alloc_vec_int(10);
    vec_int_push(&vec, 20);
    vec_int_push(&vec, 40);

    print_vec();
    vec_int_append(&vec, data, 4);
    print_vec();
    vec_int_append(&vec, data, 4);
    print_vec();
    vec_int_push(&vec, 145);
    print_vec();
    vec_int_append(&vec, data, 4);
    print_vec();
    vec_int_pop(&vec);
    print_vec();
    vec_int_remove(&vec, 3);
    print_vec();
    vec_int_insert(&vec, 3, 1024);
    print_vec();

    vec_int_free(&vec);

    return 0;
}
