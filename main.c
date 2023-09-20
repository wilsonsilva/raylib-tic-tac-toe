#include "raylib.h"
#include "stdio.h"

#define HUD_GAP 50

#define DARK_GREY  CLITERAL(Color){ 147, 143, 172, 255 }
#define LIGHT_GREY CLITERAL(Color){ 223, 222, 230, 255 }
#define LIGHT_RED  CLITERAL(Color){ 249,  35, 100, 255 }

void drawHud() {
    DrawText("YOU LOSE!", 120, 30, 30, LIGHT_RED);
    DrawText("Press R to restart", 100, 60, 20, DARK_GREY);
}

void drawBoard() {
    // Vertical lines
    DrawRectangle(160, 80 + HUD_GAP, 2, 240, LIGHT_GREY);
    DrawRectangle(240, 80 + HUD_GAP, 2, 240, LIGHT_GREY);

    // Horizontal lines
    DrawRectangle(80, 160 + HUD_GAP, 240, 2, LIGHT_GREY);
    DrawRectangle(80, 240 + HUD_GAP, 240, 2, LIGHT_GREY);
}

void drawMove(Texture2D shape, int boardX, int boardY) {
    int x = (boardX + 1) * 80;
    int y = HUD_GAP + (boardY + 1) * 80;

    DrawTexture(shape, x, y, WHITE);
}

int main(void)
{
    const int screenWidth = 400;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");

    Texture2D circle = LoadTexture("resources/textures/circle.png");
    Texture2D cross  = LoadTexture("resources/textures/cross.png");

    SetTargetFPS(60);

    // During development, align the screen to the right edge of the screen
    SetWindowPosition(1100, 300);

    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            puts("Mouse button pressed");
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        drawHud();
        drawBoard();

        drawMove(cross, 0, 0);
        drawMove(cross, 1, 1);
        drawMove(cross, 2, 2);

        drawMove(circle, 0, 2);
        drawMove(circle, 0, 1);
        drawMove(circle, 1, 2);

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(circle);
    UnloadTexture(cross);

    CloseWindow();

    return 0;
}