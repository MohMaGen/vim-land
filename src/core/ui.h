#pragma once

#include <types.h>


typedef struct container {
    px_size_t size;
    px_pos_t pos;
} container_t;


void draw_container(container_t container);
