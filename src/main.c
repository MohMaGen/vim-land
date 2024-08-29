#include "shaders.h"
#include <graphic.h>
#include <game.h>

int main() {
    init_game();
    init_shaders();

    while (!should_clsoe()) {
        draw_graphics();
    }

    free_shaders();
    free_game();

    return 0;
}
