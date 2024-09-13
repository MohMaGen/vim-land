#include <stdlib.h>
#include <types.h>

typedef struct { int a,b; } key_type;
typedef struct { int len; char *data;} value_type;
#define avg_elements_per_layer 10

typedef struct arena_hsmap_name_pair {
    key_type key; value_type value;
} arena_hsmap_name_pair_t;

typedef struct arena_hsmap_name_list {
    size_t first;
} arena_hsmap_name_list_t;

typedef union arena_hsmap_name_unit {
    struct { size_t next; arena_hsmap_name_pair_t pair; };
    arena_hsmap_name_list_t list;
} arena_hsmap_name_unit;

typedef struct arena_hsmap_name {
    arena_hsmap_name_unit *data;
    size_t len, cap, order;
} arena_hsmap_name_t;

arena_hsmap_name_t make_arena_hsmap_name(void);
void arena_hsmap_name_pushp (arena_hsmap_name_t *map, arena_hsmap_name_pair_t pair);
void arena_hsmap_name_push  (arena_hsmap_name_t *map, key_type key, value_type value);


int main(void) {
    //arena_hsmap_name_t map = make_arena_hsmap_name();

    return 0;
}

arena_hsmap_name_t make_arena_hsmap_name(void) {
    size_t lists = get_hsmap_primes()[0];
    size_t cap = lists * (avg_elements_per_layer + 1);
    arena_hsmap_name_unit *data = malloc(lists * (avg_elements_per_layer + 1) * sizeof(arena_hsmap_name_unit));
    for (size_t i = 0; i < lists; i++) {
        data[i].list = (arena_hsmap_name_list_t) { 0 };
    }
    return (arena_hsmap_name_t) {data, 0, cap, 0};
}

size_t hash_func(key_type key) {
    return *((size_t*)&key);
}

inline void __arena_hsmap_name_push_to_data(arena_hsmap_name_unit *data, size_t len, size_t cap, size_t order, arena_hsmap_name_pair_t pair) {
    size_t *next, hash;

    hash = hash_func(pair.key) % get_hsmap_primes()[order];
    data[len].pair = pair;
    data[len].next = 0;

    next = &data[hash].list.first;
    while (*next != 0) next = &data[*next].next;
    *next = len;
}

void arena_hsmap_name_pushp(arena_hsmap_name_t *map, arena_hsmap_name_pair_t pair) {
    if (map->len >= map->cap) {
        size_t lists = get_hsmap_primes()[map->order], new_lists = get_hsmap_primes()[map->order++];

        size_t new_cap =  new_lists * (avg_elements_per_layer + 1);
        arena_hsmap_name_unit *data = malloc(new_cap * sizeof(arena_hsmap_name_unit));
        for (size_t i = 0; i < new_lists; i++) {
            data[i].list = (arena_hsmap_name_list_t) { 0 };
        }

        size_t pair_idx, len = 0;
        for (size_t list_idx = 0; list_idx < lists; list_idx++) {
            pair_idx = map->data[list_idx].list.first;
            while (pair_idx != 0) {
                __arena_hsmap_name_push_to_data(data, len++, new_cap, map->order, map->data[pair_idx].pair);
            }
        }
        map->data = data;
        map->cap  = new_cap;
    }
    __arena_hsmap_name_push_to_data(map->data, map->len++, map->cap, map->order, pair);
}


void arena_hsmap_name_push(arena_hsmap_name_t *map, key_type key, value_type value) {
    arena_hsmap_name_pushp(map, (arena_hsmap_name_pair_t) { key, value });
}
