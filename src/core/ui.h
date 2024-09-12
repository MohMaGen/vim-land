#pragma once

#include <types.h>

typedef struct color {
    uint8_t r,g,b,a;
} color_t;

#define white_color_v ((color_t) { 255, 255, 255, 255 });
#define bacl_color_v ((color_t) {0, 0, 0, 255});
#define rgb_color(r, g, b) ((color_t) {r, g, b, 255});

color_t hex_color(uint32_t color);

typedef struct container {
    px_size_t size;
    px_pos_t pos;
    color_t bg_fill;
} container_t;


void draw_container(container_t container);
