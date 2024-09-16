#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct german_string {
    unsigned int len;
    union {
        char prefix[4];
        int prefix_int;
    };
    union {
        union {
            char tail[8];
            long tail_int;
        };
        struct { char *long_str; };
    };
};


struct str {
    char *data;
    size_t len;
};

struct string {
    char *data;
    size_t len, cap;
};

struct german_string mk_german_string(const char *str, unsigned int len);
int german_string_eq(struct german_string fst, struct german_string snd);

int main(void) {
    printf("Size of german_string: %zu bytes\n", sizeof(struct german_string));

    struct german_string
        short_str      = mk_german_string("short str", 10),
        short_str_copy = mk_german_string("short str", 10),
        short_str_oth  = mk_german_string("shodt str", 10),
        long_str       = mk_german_string("very long string", 17),
        long_str_oth   = mk_german_string("very long strind", 17),
        long_str_copy  = mk_german_string("very long string", 17);

    printf("short str: '%.*s', long string: '%.*s'.\n", short_str.len, short_str.prefix, long_str.len, long_str.long_str);
    printf("short str eq: %d, neq: %d.\n", german_string_eq(short_str, short_str_copy),  german_string_eq(short_str, short_str_oth));
    printf("long str eq: %d, neq: %d.\n", german_string_eq(long_str, long_str_copy),  german_string_eq(long_str, long_str_oth));

    return 0;
}

struct german_string mk_german_string(const char *str, unsigned int len) {
    struct german_string res;

    res.len = len;

    if (len <= 12) {
        res.prefix_int = 0x0;
        res.tail_int = 0x0;
        memcpy(res.prefix, str, len);
    } else {
        res.long_str = malloc(len * sizeof(char));
        memcpy(res.long_str, str, len);
    }

    return res;
}

int german_string_eq(struct german_string fst, struct german_string snd) {
    if (fst.len != snd.len) return 0;

    if (fst.len <= 12) {
        return fst.prefix_int == snd.prefix_int && fst.tail_int == snd.tail_int;
    } else {
        return memcmp(fst.long_str, snd.long_str, fst.len) == 0;
    }
}
