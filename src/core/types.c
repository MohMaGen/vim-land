#include <types.h>


impl_opt_(int, int)

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
        &filter_next,
    };
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

impl_vec_(uint8,  uint8_t)
impl_vec_(uint16, uint16_t)
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
