#include <stdio.h>
#include <stdlib.h>
#include <types.h>


typedef struct { int a,b; } key_type;
typedef struct { int len; char *data;} value_type;
#define avg_elements_per_layer 10

size_t hash_func(key_type key) {
    return *((size_t*)&key);
}

int eq_func(key_type fst, key_type snd) {
    return fst.a == snd.a && fst.b == snd.b;
}


typedef struct arena_hsmap_name_pair {
    key_type key; value_type value;
} arena_hsmap_name_pair_t;
opt_(arena_hsmap_name_pair, arena_hsmap_name_pair_t*);

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
void        free_arena_hsmap_name  (arena_hsmap_name_t *map);

void        arena_hsmap_name_insertp (arena_hsmap_name_t *map, arena_hsmap_name_pair_t pair);
void        arena_hsmap_name_insert  (arena_hsmap_name_t *map, key_type key, value_type value);
void        arena_hsmap_name_remove  (arena_hsmap_name_t *map, key_type key);
value_type *arena_hsmap_name_at      (arena_hsmap_name_t *map, key_type key);

typedef struct arena_hsmap_name_iter {
    arena_hsmap_name_unit *data; size_t list_idx, row_idx, lists;
} arena_hsmap_name_iter_t;
iter_c arena_hsmap_name_iter(arena_hsmap_name_t *map);
opt_ptr_c arena_hsmap_name_iter_next(void *self);

int main(void) {
    arena_hsmap_name_t map = make_arena_hsmap_name();

    arena_hsmap_name_insert(&map, (key_type) { 10, 10 }, (value_type) { 20, "Hello" });
    arena_hsmap_name_insert(&map, (key_type) { 120, 10 }, (value_type) { 20, "Hello" });

    value_type *fst = arena_hsmap_name_at(&map, (key_type) { 10, 10 });
    printf("fst: (%d %s)\n", fst->len, fst->data);

    value_type *snd = arena_hsmap_name_at(&map, (key_type) { 120, 10 });
    printf("snd: (%d %s)\n", snd->len, snd->data);
    arena_hsmap_name_remove(&map, (key_type) { 120, 10 });
    snd = arena_hsmap_name_at(&map, (key_type) { 120, 10 });
    printf("snd: %d (%ld)\n", snd == NULL, (unsigned long) snd);

    arena_hsmap_name_insert(&map, (key_type) { 10, 112 }, (value_type) { 20, "Hello" });
    arena_hsmap_name_insert(&map, (key_type) { 120, 12123 }, (value_type) { 20, "Hello" });
    arena_hsmap_name_insert(&map, (key_type) { 120, 1212 }, (value_type) { 20, "Helloiii" });

    iter_c iter = arena_hsmap_name_iter(&map);
    for_each(it, iter) {
        arena_hsmap_name_pair_t *pair = unwrap_ptr(arena_hsmap_name_pair_t, it);
        if (pair == NULL) continue;

        printf("(%d, %d): [%d, %s]\n", pair->key.a, pair->key.b, pair->value.len, pair->value.data);
    }

    free_arena_hsmap_name(&map);
    return 0;
}

arena_hsmap_name_t make_arena_hsmap_name(void) {
    size_t lists = get_hsmap_primes()[0];
    size_t cap = lists * (avg_elements_per_layer + 1);
    arena_hsmap_name_unit *data = malloc(lists * (avg_elements_per_layer + 1) * sizeof(arena_hsmap_name_unit));
    for (size_t i = 0; i < lists; i++) {
        data[i].list = (arena_hsmap_name_list_t) { 0 };
    }
    return (arena_hsmap_name_t) {data, lists, cap, 0};
}


void __arena_hsmap_name_push_to_data(arena_hsmap_name_unit *data, size_t len, size_t cap, size_t order,
        arena_hsmap_name_pair_t pair)
{
    size_t *next, hash, primes;

    primes = get_hsmap_primes()[order];

    hash = hash_func(pair.key) % primes;
    data[len].pair = pair;
    data[len].next = 0;

    next = &data[hash].list.first;
    while (*next != 0) next = &data[*next].next;
    *next = len;
}

void arena_hsmap_name_insertp(arena_hsmap_name_t *map, arena_hsmap_name_pair_t pair) {
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


void arena_hsmap_name_insert(arena_hsmap_name_t *map, key_type key, value_type value) {
    arena_hsmap_name_insertp(map, (arena_hsmap_name_pair_t) { key, value });
}

value_type *arena_hsmap_name_at(arena_hsmap_name_t *map, key_type key)
{
    size_t hash, curr;

    hash = hash_func(key) % get_hsmap_primes()[map->order];

    curr = map->data[hash].list.first;
    while (curr != 0) {
        if (eq_func(map->data[curr].pair.key, key)) {
            return &map->data[curr].pair.value;
        }
        curr = map->data[curr].next;
    }

    return NULL;
}

void free_arena_hsmap_name(arena_hsmap_name_t *map) {
    map->len = 0;
    map->cap = 0;
    map->order = 0;
    free(map->data);
}

void arena_hsmap_name_remove(arena_hsmap_name_t *map, key_type key) {
    size_t hash, curr, prev = 0;

    hash = hash_func(key) % get_hsmap_primes()[map->order];

    curr = map->data[hash].list.first;
    while (curr != 0) {
        if (eq_func(map->data[curr].pair.key, key)) {
            if (prev == 0) {
                map->data[hash].list.first = map->data[curr].next;
            } else {
                map->data[prev].next = map->data[curr].next;
            }
        }
        prev = curr;
        curr = map->data[curr].next;
    }
}

iter_c arena_hsmap_name_iter(arena_hsmap_name_t *map) {
    arena_hsmap_name_iter_t *iter = malloc(sizeof(arena_hsmap_name_iter_t));

    *iter = (arena_hsmap_name_iter_t) {map->data, 0, 0, get_hsmap_primes()[map->order]};

    return (iter_c) { (void*)iter, &arena_hsmap_name_iter_next };
}

opt_ptr_c arena_hsmap_name_iter_next(void *self) {
    arena_hsmap_name_iter_t *self_c = (arena_hsmap_name_iter_t*)self;
    arena_hsmap_name_pair_t pair;


    if (self_c->row_idx == 0) {
        self_c->list_idx++;
        while (self_c->list_idx < self_c->lists && self_c->data[self_c->list_idx].list.first == 0)
            self_c->list_idx++;

        if (self_c->list_idx >= self_c->lists) return none_opt_f32();

        self_c->row_idx = self_c->data[self_c->list_idx].list.first;
    }

    pair = self_c->data[self_c->row_idx].pair;
    self_c->row_idx = self_c->data[self_c->row_idx].next;

    return alloc_opt_arena_hsmap_name_pair(&pair);
}

impl_opt_(arena_hsmap_name_pair, arena_hsmap_name_pair_t *)
