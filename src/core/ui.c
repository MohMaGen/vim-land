#include "raylib.h"
#include "shaders.h"
#include <ui.h>


void draw_container(container_t container) {
    begin_shader_mode(fill_rect_v);
    end_shader_mode();
}


color_t hex_color(uint32_t color) {
    uint8_t r,g,b,a;
    if (color > 0xffffff) {
        r = color / 0x1000000; color %= 0x1000000;
        g = color / 0x10000; color %= 0x10000;
        b = color / 0x100; color %= 0x100;
        a = color;
    } else if (color > 0xffff) {
        r = color / 0x10000; color %= 0x10000;
        g = color / 0x100; color %= 0x100;
        b = color;
        a = 0xff;
    } else if (color > 0xfff) {
        r = (color / 0x1000) * 0x10 + color / 0x1000; color %= 0x1000;
        g = (color / 0x100) * 0x10 + color / 0x100; color %= 0x100;
        b = (color / 0x10) * 0x10 + color / 0x10; color %= 0x10;
        a = color * 0x10 + color;
    } else if (color > 0xff) {
        r = (color / 0x100) * 0x10 + color / 0x100; color %= 0x100;
        g = (color / 0x10) * 0x10 + color / 0x10; color %= 0x10;
        b = color * 0x10 + color;
        a = 0xFF;
    } else if (color > 0xf) {
        r = color;
        g = color;
        b = color;
        a = color;
    } else {
        r = color * 0x10 + color;
        g = color * 0x10 + color;
        b = color * 0x10 + color;
        a = color * 0x10 + color;
    }
    return (color_t) { r, g, b, a };
}
