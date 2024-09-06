#pragma once
#include <types.h>


typedef struct shader {
    unsigned int id;
    vec_int_t default_locs;
    vec_int_t custom_locs;
} shader_t;

typedef enum shader_name {
    fill_rect_v = 0
} shader_name_e;

void init_shaders(void);
void free_shaders(void);

shader_t get_shader(shader_name_e name);
void set_shader_uniform(shader_name_e name, size_t uniform_idx, void *data, int uniform_type);

void begin_shader_mode(shader_name_e name);
void end_shader_mode(void);

const char *get_fill_rect_fragment_shader(void);
