#pragma once

#include <types.h>

typedef struct border {
    color_t border_color;
    float   border_width;
    float   border_radius;
} border_t;

#define mk_border(color_hex, border_width, border_radius) ((border_t) {hex_color(color_hex), border_width, border_radius})

typedef struct container {
    fpx_pos_t   pos;
    fpx_size_t  size;
    color_t     bg_fill;

    border_t    border;
} container_t;


void draw_container(container_t container);
