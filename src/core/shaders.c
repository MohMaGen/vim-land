#include "types.h"
#include <raylib.h>
#include <shaders.h>

vec_(shader, shader_t);

vec_shader_t shaders;

shader_t rlsh2sht(Shader shader) {
    return ((shader_t) { shader.id, make_vec_int(shader.locs, 32), alloc_vec_int(32) });
}

Shader sht2rls(shader_t shader) {
    return ((Shader) { shader.id, shader.default_locs.data });
}


#define load_shader(vs, fs) rlsh2sht(LoadShaderFromMemory(vs, fs))
#define get_location(shader, location) vec_int_push(&shader.custom_locs,\
            GetShaderLocation(sht2rls(shader), #location))

void begin_shader_mode(shader_name_e name) {
    BeginShaderMode(sht2rls(get_shader(name)));
}
void end_shader_mode(void) {
    EndShaderMode();
}

void init_shaders(void) {
    shaders = alloc_vec_shader(20);

    shader_t fill_rect = load_shader(0, get_fill_rect_fragment_shader());
    get_location(fill_rect, upper_left);
    get_location(fill_rect, width_height);
    get_location(fill_rect, corner_radius);
    get_location(fill_rect, border_width);
    get_location(fill_rect, border_color);
    vec_shader_push(&shaders, fill_rect);
}

void free_shaders(void) {
    iter_c iter = vec_shader_iter(&shaders);
    for_each(shader_it, iter) {
        shader_t *shader = unwrap_opt(opt_vec_shader_t, shader_it);
        UnloadShader(sht2rls(*shader));
        vec_int_free(&shader->custom_locs);
    }
    vec_shader_free(&shaders);
}

shader_t get_shader(shader_name_e name) {
    shader_t *shader = vec_shader_at(&shaders, (size_t)name);
    return *shader;
}


impl_vec_(shader, shader_t)
