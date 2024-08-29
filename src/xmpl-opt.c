#include <types.h>
#include <stdio.h>


opt_ptr_c get_number() {
    int number;
    char buffer[100];

    fgets(buffer, 100, stdin);
    int r = sscanf(buffer, "%d", &number);
    if (r < 1) {
        return none_opt_int();
    } else {
        return alloc_opt_int(number);
    }
}


int main(void) {
    while (1) {
        fprintf(stdout, "Enter number: ");

        opt_ptr_c number_opt = get_number();
        if (number_opt.is_some(number_opt.self)) {
            fprintf(stdout, "%d\n", unwrap_opt(opt_int_t, number_opt));
        } else {
            fprintf(stderr, "Invalid format!\n");
        }

        free(number_opt.self);
        fflush(stdout);
        fflush(stderr);
        fflush(stdin);
    }

    return 0;
}
