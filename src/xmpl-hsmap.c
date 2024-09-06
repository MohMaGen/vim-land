#include <stdio.h>
#include <types.h>


void print_map_structure(hsmap_strs_t *map) {
    iter_c rows = vec_hsmap_strs_data_iter(&map->data);
    printf("{ map [ \n");
    int columns = 1;
    int curr = 0;
    for_each(row_it, rows) {
        vec_hsmap_strs_row_t *row = unwrap_opt(opt_vec_hsmap_strs_data_t, row_it);

        iter_c pairs = vec_hsmap_strs_row_iter(row);
        printf("[ ");
        for_each(pair_it, pairs) {
            hsmap_strs_pair_t *pair = unwrap_opt(opt_vec_hsmap_strs_row_t, pair_it);
            printf("(`%s` => `%s`) ", pair->key, pair->value);
        }
        printf("], %s", (curr++ % columns == 0) ? "\n" : "     ");
    }
    printf("]}\n");
}


#define print_map(){                                                                    \
        iter_c iter = hsmap_strs_iter(&map);                                            \
        printf("{ ");                                                                   \
        for_each(pair_it, iter) {                                                       \
            hsmap_strs_pair_t *pair = unwrap_opt(opt_vec_hsmap_strs_row_t, pair_it);    \
            printf("[`%s`:`%s`] ", pair->key, pair->value);                             \
        }                                                                               \
        printf("}\n");                                                                  \
    }                                                                                   \

iter_c get_pairs_i(void);
hsmap_strs_pair_t *get_pairs(void);

int main(void) {
    hsmap_strs_t map = alloc_hsmap_strs(2);
    hsmap_strs_insert(&map, "value", "10");

    char** value = hsmap_strs_at(&map, "value");
    printf("`value`: `%s`\n", *value);
    print_map()

    hsmap_strs_insert(&map, "value", "200-0-0");
    value = hsmap_strs_at(&map, "value");
    printf("`value`: `%s`\n", *value);

    hsmap_strs_insert(&map, "value2", "200-0-0");
    print_map()

    hsmap_strs_insert(&map, "value3", "200-0-0");
    print_map()

    hsmap_strs_remove(&map, "value3");
    print_map()

    hsmap_strs_remove(&map, "value123");
    print_map()

    hsmap_strs_append_it(&map, get_pairs_i());
    print_map_structure(&map);
    puts("\n\n\n\n\n\n\n\n\n\n\n\n");
    hsmap_strs_append(&map, get_pairs(), 100);
    print_map_structure(&map);

    hsmap_strs_free(&map);

    return 0;
}

hsmap_strs_pair_t pairs[] = {
    { "var-1", "bi" },
    { "var-2", "bi" },
    { "var-3", "bi" },
    { "var-4", "bi" },
    { "var-5", "bi" },
    { "var-6", "bi" },
    { "var-7", "bi" },
    { "var-8", "bi" },
    { "var-9", "bi" },
    { "var-10", "bi" },
    { "var-11", "bi" },
    { "var-12", "bi" },
    { "var-13", "bi" },
    { "var-14", "bi" },
    { "var-15", "bi" },
    { "var-16", "bi" },
    { "var-17", "bi" },
    { "var-18", "bi" },
    { "var-19", "bi" },
    { "var-20", "bi" },
    { "var-21", "bi" },
    { "var-22", "bi" },
    { "var-23", "bi" },
    { "var-24", "bi" },
    { "var-25", "bi" },
    { "var-26", "bi" },
    { "var-27", "bi" },
    { "var-28", "bi" },
    { "var-29", "bi" },
    { "var-30", "bi" },
    { "var-31", "bi" },
    { "var-32", "bi" },
    { "var-33", "bi" },
    { "var-34", "bi" },
    { "var-35", "bi" },
    { "var-36", "bi" },
    { "var-37", "bi" },
    { "var-38", "bi" },
    { "var-39", "bi" },
    { "var-40", "bi" },
    { "var-41", "bi" },
    { "var-42", "bi" },
    { "var-43", "bi" },
    { "var-44", "bi" },
    { "var-45", "bi" },
    { "var-46", "bi" },
    { "var-47", "bi" },
    { "var-48", "bi" },
    { "var-49", "bi" },
    { "var-50", "bi" },
    { "var-51", "bi" },
    { "var-52", "bi" },
    { "var-53", "bi" },
    { "var-54", "bi" },
    { "var-55", "bi" },
    { "var-56", "bi" },
    { "var-57", "bi" },
    { "var-58", "bi" },
    { "var-59", "bi" },
    { "var-60", "bi" },
    { "var-61", "bi" },
    { "var-62", "bi" },
    { "var-63", "bi" },
    { "var-64", "bi" },
    { "var-65", "bi" },
    { "var-66", "bi" },
    { "var-67", "bi" },
    { "var-68", "bi" },
    { "var-69", "bi" },
    { "var-70", "bi" },
    { "var-71", "bi" },
    { "var-72", "bi" },
    { "var-73", "bi" },
    { "var-74", "bi" },
    { "var-75", "bi" },
    { "var-76", "bi" },
    { "var-77", "bi" },
    { "var-78", "bi" },
    { "var-79", "bi" },
    { "var-80", "bi" },
    { "var-81", "bi" },
    { "var-82", "bi" },
    { "var-83", "bi" },
    { "var-84", "bi" },
    { "var-85", "bi" },
    { "var-86", "bi" },
    { "var-87", "bi" },
    { "var-88", "bi" },
    { "var-89", "bi" },
    { "var-90", "bi" },
    { "var-91", "bi" },
    { "var-92", "bi" },
    { "var-93", "bi" },
    { "var-94", "bi" },
    { "var-95", "bi" },
    { "var-96", "bi" },
    { "var-97", "bi" },
    { "var-98", "bi" },
    { "var-99", "bi" },
    { "var-100", "bi" },
};

array_iter_(pair, hsmap_strs_pair_t);
impl_array_iter_(pair, hsmap_strs_pair_t)
iter_c get_pairs_i(void) {
    return alloc_array_iter_pair(pairs, 100);
}

hsmap_strs_pair_t pairs_lol[] = {
    { "lol_Adfs-1", "bi" },
    { "lol_Adfs-2", "bi" },
    { "lol_Adfs-3", "bi" },
    { "lol_Adfs-4", "bi" },
    { "lol_Adfs-5", "bi" },
    { "lol_Adfs-6", "bi" },
    { "lol_Adfs-7", "bi" },
    { "lol_Adfs-8", "bi" },
    { "lol_Adfs-9", "bi" },
    { "lol_Adfs-10", "bi" },
    { "lol_Adfs-11", "bi" },
    { "lol_Adfs-12", "bi" },
    { "lol_Adfs-13", "bi" },
    { "lol_Adfs-14", "bi" },
    { "lol_Adfs-15", "bi" },
    { "lol_Adfs-16", "bi" },
    { "lol_Adfs-17", "bi" },
    { "lol_Adfs-18", "bi" },
    { "lol_Adfs-19", "bi" },
    { "lol_Adfs-20", "bi" },
    { "lol_Adfs-21", "bi" },
    { "lol_Adfs-22", "bi" },
    { "lol_Adfs-23", "bi" },
    { "lol_Adfs-24", "bi" },
    { "lol_Adfs-25", "bi" },
    { "lol_Adfs-26", "bi" },
    { "lol_Adfs-27", "bi" },
    { "lol_Adfs-28", "bi" },
    { "lol_Adfs-29", "bi" },
    { "lol_Adfs-30", "bi" },
    { "lol_Adfs-31", "bi" },
    { "lol_Adfs-32", "bi" },
    { "lol_Adfs-33", "bi" },
    { "lol_Adfs-34", "bi" },
    { "lol_Adfs-35", "bi" },
    { "lol_Adfs-36", "bi" },
    { "lol_Adfs-37", "bi" },
    { "lol_Adfs-38", "bi" },
    { "lol_Adfs-39", "bi" },
    { "lol_Adfs-40", "bi" },
    { "lol_Adfs-41", "bi" },
    { "lol_Adfs-42", "bi" },
    { "lol_Adfs-43", "bi" },
    { "lol_Adfs-44", "bi" },
    { "lol_Adfs-45", "bi" },
    { "lol_Adfs-46", "bi" },
    { "lol_Adfs-47", "bi" },
    { "lol_Adfs-48", "bi" },
    { "lol_Adfs-49", "bi" },
    { "lol_Adfs-50", "bi" },
    { "lol_Adfs-51", "bi" },
    { "lol_Adfs-52", "bi" },
    { "lol_Adfs-53", "bi" },
    { "lol_Adfs-54", "bi" },
    { "lol_Adfs-55", "bi" },
    { "lol_Adfs-56", "bi" },
    { "lol_Adfs-57", "bi" },
    { "lol_Adfs-58", "bi" },
    { "lol_Adfs-59", "bi" },
    { "lol_Adfs-60", "bi" },
    { "lol_Adfs-61", "bi" },
    { "lol_Adfs-62", "bi" },
    { "lol_Adfs-63", "bi" },
    { "lol_Adfs-64", "bi" },
    { "lol_Adfs-65", "bi" },
    { "lol_Adfs-66", "bi" },
    { "lol_Adfs-67", "bi" },
    { "lol_Adfs-68", "bi" },
    { "lol_Adfs-69", "bi" },
    { "lol_Adfs-70", "bi" },
    { "lol_Adfs-71", "bi" },
    { "lol_Adfs-72", "bi" },
    { "lol_Adfs-73", "bi" },
    { "lol_Adfs-74", "bi" },
    { "lol_Adfs-75", "bi" },
    { "lol_Adfs-76", "bi" },
    { "lol_Adfs-77", "bi" },
    { "lol_Adfs-78", "bi" },
    { "lol_Adfs-79", "bi" },
    { "lol_Adfs-80", "bi" },
    { "lol_Adfs-81", "bi" },
    { "lol_Adfs-82", "bi" },
    { "lol_Adfs-83", "bi" },
    { "lol_Adfs-84", "bi" },
    { "lol_Adfs-85", "bi" },
    { "lol_Adfs-86", "bi" },
    { "lol_Adfs-87", "bi" },
    { "lol_Adfs-88", "bi" },
    { "lol_Adfs-89", "bi" },
    { "lol_Adfs-90", "bi" },
    { "lol_Adfs-91", "bi" },
    { "lol_Adfs-92", "bi" },
    { "lol_Adfs-93", "bi" },
    { "lol_Adfs-94", "bi" },
    { "lol_Adfs-95", "bi" },
    { "lol_Adfs-96", "bi" },
    { "lol_Adfs-97", "bi" },
    { "lol_Adfs-98", "bi" },
    { "lol_Adfs-99", "bi" },
    { "lol_Adfs-100", "bi" },
};

hsmap_strs_pair_t *get_pairs(void) {
    return pairs_lol;
}
