#include "raylib.h"
#include "shaders.h"
#include <ui.h>


void draw_container(container_t container) {
    float pos[2] = { container.pos.x, ((float) GetScreenHeight()) - container.pos.y };

    set_shader_uniform(fill_rect_v, fr_upper_left_v,    &pos,                               SHADER_UNIFORM_VEC2);
    set_shader_uniform(fill_rect_v, fr_width_height_v,  &container.size,                    SHADER_UNIFORM_VEC2);
    set_shader_uniform(fill_rect_v, fr_corner_raidus_v, &container.border.border_radius,    SHADER_UNIFORM_FLOAT);
    set_shader_uniform(fill_rect_v, fr_border_width_v,  &container.border.border_width,     SHADER_UNIFORM_FLOAT);
    set_shader_uniform(fill_rect_v, fr_border_color_v,  &container.border.border_color,     SHADER_UNIFORM_IVEC4);

    begin_shader_mode(fill_rect_v);
    DrawRectangle(container.pos.x, container.pos.y, container.size.width, container.size.height, color2rl(container.bg_fill));
    end_shader_mode();
}
