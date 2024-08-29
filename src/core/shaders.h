#pragma once
#include <types.h>


typedef struct shader {
    unsigned int id;
    vec_int_t default_locs;
    vec_int_t custom_locs;
} shader_t;

typedef enum shader_name {
    fill_rect_e = 0
} shader_name_e;

void init_shaders(void);
void free_shaders(void);
shader_t get_shader(shader_name_e name);
void set_shader_uniform(shader_name_e name, size_t uniform_idx,
        void *data, int uniform_type);

const char *get_fill_rect_fragment_shader(void);
