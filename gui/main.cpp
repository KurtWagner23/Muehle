#include "board.hpp"
#include "raylib.h"

int main() {
    InitWindow(800, 600, "Mühle GUI mit Raylib");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hallo, Mühle GUI!", 250, 280, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
