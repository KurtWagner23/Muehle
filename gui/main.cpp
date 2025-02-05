#include "board.hpp"
#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Muehle Game");

    Texture2D boardTexture = LoadTexture("assets/muehle.png");
    Vector2 piecePos = {400.0f, 300.0f};

    SetTargetFPS(60);

    std::vector<Vector2> positions = {};

    ClearBackground(RAYWHITE);
    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawTexturePro(
            boardTexture,
            {0, 0, (float)boardTexture.width, (float)boardTexture.height},
            {0, 0, (float)screenWidth, (float)screenHeight - 200.0},
            {0, -200},
            0.0f,
            WHITE);

        Vector2 mousePosition = GetMousePosition();
        piecePos = mousePosition;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            positions.push_back(piecePos);
        }
        for (auto pos : positions) {
            DrawCircleV(pos, 20.0f, RED);
        }

        EndDrawing();
    }

    UnloadTexture(boardTexture);

    CloseWindow();
    return 0;
}
