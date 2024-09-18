#include "raylib.h"
#include "types.h"
#include "ui.h"
#include <graphic.h>

void draw_graphics(void) {
    BeginDrawing();
    ClearBackground(WHITE);

    draw_container((container_t) {
            mkfpx_pos((float)GetScreenWidth() / 2 - 150., (float)GetScreenHeight() / 2 - 50. - 150. ), /* pos */
            mkfpx_size(300, 100), /* size */
            hex_color(0xFF2200FF), /* bg_fill */
            mk_border(0x22FF00FF, 5., 10.) /* border */
    });
    draw_container((container_t) {
            mkfpx_pos((float)GetScreenWidth() / 2 - 150., (float)GetScreenHeight() / 2 - 50. ), /* pos */
            mkfpx_size(300, 100), /* size */
            hex_color(0xAA2244FF), /* bg_fill */
            mk_border(0x22AA44FF, 5., 10.) /* border */
    });
    draw_container((container_t) {
            mkfpx_pos((float)GetScreenWidth() / 2 - 150., (float)GetScreenHeight() / 2 - 50. + 150. ), /* pos */
            mkfpx_size(300, 100), /* size */
            hex_color(0xFF2200FF), /* bg_fill */
            mk_border(0x22FF00FF, 5., 10.) /* border */
    });

    EndDrawing();
}


