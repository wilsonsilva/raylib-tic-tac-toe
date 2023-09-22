#include "raylib.h"
#include "animations.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define HUD_GAP 50

#define DARK_GREY  CLITERAL(Color){ 147, 143, 172, 255 }
#define LIGHT_GREY CLITERAL(Color){ 223, 222, 230, 255 }
#define LIGHT_RED  CLITERAL(Color){ 249,  35, 100, 255 }

static const int screenWidth = 400;
static const int screenHeight = 450;

static Texture2D circle;
static Texture2D cross;

static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

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
    int x = (boardX + 1) * 80 + 40;
    int y = HUD_GAP + (boardY + 1) * 80 + 40;

    DrawTextureEx(shape, (Vector2){x - shape.width * currentScale / 2, y - shape.height * currentScale / 2}, 0.0f, currentScale, WHITE);
}

void InitGame(void) {
    // During development, align the screen to the right edge of the screen
    SetWindowPosition(1100, 300);

    circle = LoadTexture("resources/textures/circle.png");
    cross = LoadTexture("resources/textures/cross.png");
}

void UpdateGame(void) {
    updateAnimations();
}

// Draw game (one frame)
void DrawGame(void) {
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

// Unload game variables
void UnloadGame(void) {
    UnloadTexture(circle);
    UnloadTexture(cross);
}

// Update and Draw (one frame)
void UpdateDrawFrame(void) {
    UpdateGame();
    DrawGame();
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();
    CloseWindow();

    return 0;
}