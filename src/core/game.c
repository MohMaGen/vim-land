#include <game.h>
#include <raylib.h>

void init_game(void) {
    InitWindow(300, 300, "aboba");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);
    SetWindowSize(GetScreenWidth(), GetScreenHeight());
}

void free_game(void) {
    CloseWindow();
}

int should_clsoe(void) {
    return WindowShouldClose();
}
