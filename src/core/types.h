#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct pixel_size { uint32_t widht, height; }   px_size_t;
typedef struct pixel_pair { uint32_t fst, snd; }        px_pair_t;
typedef struct pixel_pos  { uint32_t x, y; }            px_pos_t;

#define mkpx_size (width, height)   ((px_size_t) { widht, height})
#define mkpx_pair (fst, snd)        ((px_pair_t) { fst, snd})
#define mkpx_pos  (x, y)            ((px_pos_t)  { x, y})

#define px_p2size (pair)            ((px_size_t) { pair.fst, pair.snd})
#define px_p2pos  (pair)            ((px_pos_t)  { pair.fst, pair.snd})


typedef struct opt_ptr_c {
    void *self; uint8_t (*is_some)(void *);
} opt_ptr_c;
#define mk_opt_ptr(data_ptr, is_some) ((opt_ptr_c) { (void*) data_ptr, is_some })
#define unwrap_opt(type, opt) (((type *) opt.self)->data)

#define opt_(name, type)\
    typedef struct opt_## name { uint8_t is_some; type data; } opt_## name ##_t;\
    uint8_t opt_## name ##_is_some( void *);\
    opt_##name##_t make_opt_##name(type value);\
    opt_ptr_c none_opt_##name();\
    opt_ptr_c alloc_opt_##name(type value)

#define impl_opt_(name, type)\
    uint8_t opt_## name ##_is_some( void *ptr ) {\
        return ((opt_## name ##_t*)ptr)->is_some;\
    }\
    opt_##name##_t make_opt_##name(type value) {\
        return (opt_##name##_t) { 1, value };\
    }\
    opt_ptr_c none_opt_##name() {\
        opt_##name##_t *opt = malloc(sizeof(opt_##name##_t));\
        opt->is_some = 0;\
        return mk_opt_ptr(opt, &opt_## name ##_is_some);\
    }\
    opt_ptr_c alloc_opt_##name(type value) {\
        opt_##name##_t *opt = malloc(sizeof(opt_##name##_t));\
        opt->is_some = 1;\
        opt->data = value;\
        return mk_opt_ptr(opt, &opt_## name ##_is_some);\
    }\

opt_(int, int);

opt_(int8,  int8_t);
opt_(int16, int16_t);
opt_(int32, int16_t);
opt_(int64, int64_t);

opt_(uint8,  uint8_t);
opt_(uint16, uint16_t);
opt_(uint32, uint16_t);
opt_(uint64, uint64_t);

opt_(str, char *);
opt_(char, char);

opt_(f32, float);
opt_(f64, double);

typedef struct iter_c {
    void *self; opt_ptr_c (*next)(void *);
} iter_c;

typedef struct filter_ptr {
    iter_c data; int (*predicat)(opt_ptr_c);
} filter_ptr_t;

typedef struct map_ptr { 
    iter_c data; opt_ptr_c (*func)(opt_ptr_c); 
} map_ptr_t;

iter_c filter(iter_c iter, int (*predicat)(opt_ptr_c));

iter_c until(iter_c iter, int (*predicat)(opt_ptr_c));

iter_c map(iter_c iter, opt_ptr_c (*func)(opt_ptr_c));


#define for_each(it_name, it)\
    for (opt_ptr_c it_name = it.next(iter.self); it_name.is_some(it_name.self); it_name = it.next(iter.self))

#define array_iter_(name, type)\
    typedef struct array_iter_##name { type *data; size_t len, curr; } array_iter_##name##_t;\
    opt_(array_iter_##name, type*);\
    opt_ptr_c array_iter_##name##_next(void *self);\
    iter_c alloc_array_iter_##name(type *data, size_t len)\

#define impl_array_iter_(name, type)\
    impl_opt_(array_iter_##name, type*)\
    opt_ptr_c array_iter_##name##_next(void *self) {\
        array_iter_##name##_t *self_c = (array_iter_##name##_t*) self;\
        if (self_c->curr >= self_c->len) {\
            return none_opt_array_iter_##name();\
        }\
        return alloc_opt_array_iter_##name(self_c->data + self_c->curr++);\
    }\
    iter_c alloc_array_iter_##name(type *data, size_t len) {\
        array_iter_##name##_t *self = malloc(sizeof(array_iter_##name##_t));\
        *self = (array_iter_##name##_t) { data, len, 0};\
        return (iter_c) {(void *) self, &array_iter_##name##_next};\
    }

array_iter_(int, int);

array_iter_(int8,  int8_t);
array_iter_(int16, int16_t);
array_iter_(int32, int16_t);
array_iter_(int64, int64_t);

array_iter_(uint8,  uint8_t);
array_iter_(uint16, uint16_t);
array_iter_(uint32, uint16_t);
array_iter_(uint64, uint64_t);

array_iter_(str, char *);
array_iter_(char, char);

array_iter_(f32, float);
array_iter_(f64, double);



#define vec_(name, type)\
    typedef struct vec_## name {\
        type *data; size_t len, capacity;\
    } vec_## name ##_t;\
    vec_## name ##_t alloc_vec_## name(size_t capacity);\
    vec_## name ##_t make_vec_## name(type *data, size_t len);\
    void  vec_## name ##_free     (vec_## name ##_t *vector);\
    void  vec_## name ##_push     (vec_## name ##_t *vector, type value);\
    void  vec_## name ##_append   (vec_## name ##_t *vector, type *data, size_t len);\
    void  vec_## name ##_pop      (vec_## name ##_t *vector);\
    type *vec_## name ##_at       (vec_## name ##_t *vector, size_t idx);\
    void  vec_## name ##_remove   (vec_## name ##_t *vector, size_t idx);\
    void  vec_## name ##_insert   (vec_## name ##_t *vector, size_t idx, type value);\
    typedef struct vec_## name ##_iter {\
        type *data; size_t curr, len;\
    } vec_## name ##_iter_t;\
    vec_## name ##_iter_t  vec_## name ##_iter(vec_## name ##_t *vector);\
    type *vec_## name ##_iter_next(vec_## name ##_iter_t *iter);\
    \
    opt_(vec_##name, type*);\
    opt_ptr_c vec_## name ##_next(vec_## name ##_iter_t *iter);\
    opt_ptr_c vec_## name ##_get(vec_## name ##_t *vector, size_t idx)\

#define impl_vec_(name, type)\
    vec_## name ##_t alloc_vec_## name(size_t capacity) {\
        return (vec_## name ##_t) { (type*)malloc( capacity * sizeof(type)), 0, capacity };\
    }\
    vec_## name ##_t make_vec_## name(type *data, size_t len) {\
        type *new_data = malloc( len * 2 * sizeof(type));\
        for (size_t i = 0; i < len; i++) new_data[i] = data[i];\
        return (vec_## name ##_t) { new_data, len, len * 2 };\
    }\
    void  vec_## name ##_free     (vec_## name ##_t *vector) {\
        vector->len = 0;\
        vector->capacity = 0;\
        free(vector->data);\
    }\
    void  vec_## name ##_append   (vec_## name ##_t *vector, type *data, size_t len) {\
        if (data == NULL) return;\
        if (vector->len + len > vector->capacity) {\
            vector->capacity += len; vector->capacity *= 2;\
            type *new_data = malloc( vector->capacity * sizeof(type));\
            for ( size_t i = 0; i < vector->len; i++) new_data[i] = vector->data[i];\
            free(vector->data);\
            vector->data = new_data;\
        }\
        for ( size_t i = 0; i < len; i++ )\
            vector->data[vector->len + i] = data[i];\
        vector->len += len;\
    }\
    void  vec_## name ##_push     (vec_## name ##_t *vector, type value) {\
        if (vector->len >= vector->capacity) {\
            vector->capacity++; vector->capacity *= 2;\
            type *new_data = malloc( vector->capacity * sizeof(type) );\
            for (size_t i = 0; i < vector->len; i++) new_data[i] = vector->data[i];\
            free(vector->data);\
            vector->data = new_data;\
        }\
        vector->data[vector->len++] = value;\
    }\
    void  vec_## name ##_pop      (vec_## name ##_t *vector) {\
        if (vector->len == 0) return;\
        vector->len--;\
    }\
    type *vec_## name ##_at       (vec_## name ##_t *vector, size_t idx) {\
        if (idx >= vector->len) return NULL;\
        return vector->data +idx;\
    }\
    void  vec_## name ##_remove   (vec_## name ##_t *vector, size_t idx) {\
        if (idx >= vector->len) return;\
        for (size_t jdx = idx+1; jdx < vector->len; jdx++) vector->data[idx++] = vector->data[jdx];\
        vector->len--;\
    }\
    void  vec_## name ##_insert   (vec_## name ##_t *vector, size_t idx, type value) {\
        if (vector->len >= vector->capacity) {\
            vector->capacity++; vector->capacity *= 2;\
            type *new_data = malloc( vector->capacity * sizeof(type) );\
            for (size_t i = 0; i < vector->len; i++) new_data[i] = vector->data[i];\
            free(vector->data);\
            vector->data = new_data;\
        }\
        for (size_t jdx = vector->len; jdx > idx; jdx--) vector->data[jdx] = vector->data[jdx-1];\
        vector->len++;\
        vector->data[idx] = value;\
    }\
    vec_## name ##_iter_t  vec_## name ##_iter(vec_## name ##_t *vector) {\
        return (vec_## name ##_iter_t) { vector->data, 0, vector->len };\
    }\
    type *vec_## name ##_iter_next(vec_## name ##_iter_t *iter) {\
        if (iter->curr >= iter->len) {\
            return NULL;\
        }\
        return iter->data + iter->curr++;\
    }\
    impl_opt_(vec_##name, type*)\
    opt_ptr_c vec_## name ##_next(vec_## name ##_iter_t *iter) {\
        if (iter->curr >= iter->len) {\
            return none_opt_vec_##name();\
        }\
        return alloc_opt_vec_##name(iter->data + iter->curr++);\
    }\
    opt_ptr_c vec_## name ##_get(vec_## name ##_t *vector, size_t idx) {\
        type *res = vec_##name##_at(vector, idx);\
        if (res == NULL) return none_opt_vec_##name();\
        return alloc_opt_vec_##name(res);\
    }\

// default vectors
vec_(int, int);

vec_(int8,  int8_t);
vec_(int16, int16_t);
vec_(int32, int16_t);
vec_(int64, int64_t);

vec_(uint8,  uint8_t);
vec_(uint16, uint16_t);
vec_(uint32, uint16_t);
vec_(uint64, uint64_t);

vec_(str, char *);

vec_(f32, float);
vec_(f64, double);



const size_t *get_hsmap_primes(void);
#define hash_map_(name, key_type, value_type)\
    typedef struct { key_type key; value_type value; } hsmap_## name ##_pair_t;\
    vec_(hsmap_## name ##_row, hsmap_## name ##_pair_t);\
    vec_(hsmap_## name ##_data, vec_hsmap_## name ##_row_t)\
    typedef struct hsmap_## name {\
        vec_hsmap_## name ##_data_t data\
        size_t len;\
    } hsmap_## name ##_t;\
    \
    hsmap_## name ##_t alloc_hsmap_## name      (size_t prime_idx);\
    \
    void        hsmap_## name ##_insert  (hsmap_## name ##_t *, key_type, value_type);\
    void        hsmap_## name ##_remove  (hsmap_## name ##_t *, key_type);\
    value_type *hsmap_## name ##_at      (hsmap_## name ##_t *, key_type);\
    \
    typedef struct hsmap_## name ##_iter {\
        vec_hsmap_## name ##_data_t data; size_t d_idx, r_idx;\
    } hsmap_## name ##_iter_t;\
    hsmap_## name ##_iter_t hsmap_## name ##_iter(hsmape_ ## name ##_t *map);\
    \



#define impl_hash_map_(name, key_type, value_type, eq_func, hash_func)\
    hsmap_## name ##_t alloc_hsmap_## name      (size_t prime_idx) {\
        hsmap_## name ##_t map;\
        size_t len = get_hsmap_primes()[prime_idx];\
        map.data = alloc_vec_## name ##_data_t(len);\
        map.len = 0;\
        for (size_t i = 0; i < len; i++) \
            vec_hsmap_## name ##_data_push(alloc_vec_hsmap_## name ##_row(len / 10));\
        \
        return map;\
    }\
    void hsmap_## name ##_insert(hsmap_## name ##_t * map, key_type key, value_type value) {\
        size_t idx = hash_func(key) % map->data.capacity;\
        map->len++;\
        vec_hsmap_## name ##_row_t *row = vec_hsmap_## name ##_data_at(map, idx);\
        vec_hsmap_## name ##_row_iter_t iter = vec_hsmap_## name ##_row_iter(row);\
        hsmap_## name ##_pair_t *curr;\
        while ((curr = vec_hsmap_## name ##_row_iter_next(&iter)) != NULL) {\
            if (eq_func(curr->key, key)) {\
                curr->value = value;\
                return;\
            }\
        }\
        vec_hsmap_## name ##_row_push(row, value);\
    }\
    void hsmap_## name ##_remove(hsmap_## name ##_t *map, key_type key) {\
        size_t idx = hash_func(key) % map->data.capacity;\
        map->len--;\
        vec_hsmap_## name ##_row_t *row = vec_hsmap_## name ##_data_at(map, idx);\
        for (size_t i = 0; i < row->len; i++) {\
            if (eq_func(row->data[i].key, key)) {\
                vec_hsmap_## name ##_row_remove(row, i);\
                return;\
            }\
        }\
    }\
    value_type *hsmap_## name ##_at(hsmap_## name ##_t *map, key_type key) {\
        size_t idx = hash_func(key) % map->data.capacity;\
        vec_hsmap_## name ##_row_t * row = vec_hsmap_## name ##_data_at(map, idx);\
        size_t i; for (i = 0; i < row->len; i++) {\
            if (eq_func(row->data[i].key, key)) {\
                break;\
            }\
        }\
        return vec_hsmap_## name ##_row_at(map, i);\
    }\
    hsmap_## name ##_iter_t hsmap_## name ##_iter(hsmape_ ## name ##_t *map) {\
        return (hsmap_## name ##_iter_t) { map->data, 0, 0 };\
    }\


