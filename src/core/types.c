#include <string.h>
#include <types.h>


impl_opt_(int, int)
impl_opt_(usize, size_t)

impl_opt_(int8,  int8_t)
impl_opt_(int16, int16_t)
impl_opt_(int32, int16_t)
impl_opt_(int64, int64_t)

impl_opt_(uint8,  uint8_t)
impl_opt_(uint16, uint16_t)
impl_opt_(uint32, uint16_t)
impl_opt_(uint64, uint64_t)

impl_opt_(str, char *)
impl_opt_(char, char)

impl_opt_(f32, float)
impl_opt_(f64, double)



opt_ptr_c filter_next(void *f) {
    struct filter_ptr *fl = (struct filter_ptr *)f;

    opt_ptr_c next;
    for (;;) {
        next = fl->data.next(fl->data.self);
        if (!next.is_some(next.self)) return none_opt_char();
        if (fl->predicat(next)) break;
    }
    return next;
}
iter_c filter(iter_c iter, int (*predicat)(opt_ptr_c)) {
    struct filter_ptr *f = malloc(sizeof(struct filter_ptr));
    *f = (filter_ptr_t) { iter, predicat };

    return (iter_c) {
        (void*) f,
        &filter_next,
    };
}

opt_ptr_c until_next(void *f) {
    struct filter_ptr *fl = (struct filter_ptr *)f;
    opt_ptr_c next = fl->data.next(fl->data.self);

    if (!next.is_some(next.self)) return none_opt_char();
    if (!fl->predicat(next)) return none_opt_char();
    return next;
}
iter_c until(iter_c iter, int (*predicat)(opt_ptr_c)) {
    struct filter_ptr *f = malloc(sizeof(struct filter_ptr));
    *f = (filter_ptr_t) { iter, predicat };

    return (iter_c) {
        (void*) f,
        &until_next,
    };
}

opt_ptr_c map_next(void *self) {
    map_ptr_t *m = (map_ptr_t *)self;

    opt_ptr_c next = m->data.next(m->data.self);

    return (!next.is_some(next.self))?  none_opt_char() : m->func(next);
}
iter_c map(iter_c iter, opt_ptr_c (*func)(opt_ptr_c)) {
    map_ptr_t *m = malloc(sizeof(map_ptr_t));
    *m = (map_ptr_t) { iter, func };
    return (iter_c) { (void*)m, &map_next };
}

impl_array_iter_(int, int)
impl_array_iter_(int8,  int8_t)
impl_array_iter_(int16, int16_t)
impl_array_iter_(int32, int16_t)
impl_array_iter_(int64, int64_t)

impl_array_iter_(uint8,  uint8_t)
impl_array_iter_(uint16, uint16_t)
impl_array_iter_(uint32, uint16_t)
impl_array_iter_(uint64, uint64_t)

impl_array_iter_(str, char *)
impl_array_iter_(char, char)

impl_array_iter_(f32, float)
impl_array_iter_(f64, double)


impl_vec_(int, int)

impl_vec_(int8,  int8_t)
impl_vec_(int16, int16_t)
impl_vec_(int32, int16_t)
impl_vec_(int64, int64_t)

impl_vec_(uint8,  uint8_t) impl_vec_(uint16, uint16_t)
impl_vec_(uint32, uint16_t)
impl_vec_(uint64, uint64_t)

impl_vec_(str, char *)

impl_vec_(f32, float)
impl_vec_(f64, double)

size_t primes[] = {
    53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
    49157, 98317, 196613, 393241, 786433, 1572869, 3145739,
    6291469, 12582917, 25165843, 50331653, 100663319, 201326611,
    402653189, 805306457, 1610612741,
};

const size_t *get_hsmap_primes(void) {
    return primes;
}

int str_eq(const char *fst, const char *snd) {
    return strcmp(fst, snd) == 0;
}
size_t str_hash(const char *str) {
    size_t len;
    size_t hash, str_iter;
    int c;

    len = strlen(str);
    hash = 5381;
    for (str_iter = 0; str_iter < len; str_iter++) {
        c = ((unsigned char*) str)[str_iter];
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

#define simpl_eq(a, b) (a == b)
#define simpl_hash(a) ((size_t) a)

impl_hash_map_(strs, char *, char *, str_eq, str_hash)
impl_hash_map_(ints, int, int, simpl_eq, simpl_hash)

impl_hash_map_(ints_8, int8_t, int8_t, simpl_eq, simpl_hash)
impl_hash_map_(ints_16, int16_t, int16_t, simpl_eq, simpl_hash)
impl_hash_map_(ints_32, int32_t, int32_t, simpl_eq, simpl_hash)
impl_hash_map_(ints_64, int64_t, int64_t, simpl_eq, simpl_hash)

impl_hash_map_(uints_8, uint8_t, uint8_t, simpl_eq, simpl_hash)
impl_hash_map_(uints_16, uint16_t, uint16_t, simpl_eq, simpl_hash)
impl_hash_map_(uints_32, uint32_t, uint32_t, simpl_eq, simpl_hash)
impl_hash_map_(uints_64, uint64_t, uint64_t, simpl_eq, simpl_hash)


impl_hsmap_str_to_(int, int)

impl_hsmap_str_to_(int8,  int8_t)
impl_hsmap_str_to_(int16, int16_t)
impl_hsmap_str_to_(int32, int16_t)
impl_hsmap_str_to_(int64, int64_t)

impl_hsmap_str_to_(uint8,  uint8_t)
impl_hsmap_str_to_(uint16, uint16_t)
impl_hsmap_str_to_(uint32, uint16_t)
impl_hsmap_str_to_(uint64, uint64_t)

impl_hsmap_str_to_(f32, float)
impl_hsmap_str_to_(f64, double)
