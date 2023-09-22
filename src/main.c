#include "raylib.h"
#include "animations.h"
#include <stdio.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define HUD_GAP 50

#define DARK_GREY  CLITERAL(Color){ 147, 143, 172, 255 }
#define LIGHT_GREY CLITERAL(Color){ 223, 222, 230, 255 }
#define LIGHT_RED  CLITERAL(Color){ 249,  35, 100, 255 }
#define EMPTY 0
#define CROSS 1
#define CIRCLE 2

Move moves[9];
int moveCount = 0;

int board[3][3];

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

void drawMove(Texture2D shape, int boardX, int boardY, float scale) {
    int x = (boardX + 1) * 80 + 40;
    int y = HUD_GAP + (boardY + 1) * 80 + 40;

    DrawTextureEx(shape, (Vector2){x - shape.width * scale / 2, y - shape.height * scale / 2}, 0.0f, scale, WHITE);
}

void drawMoves() {
    for (int i = 0; i < moveCount; i++) {
        Move move = moves[i];

        if (move.type == CROSS) {
            drawMove(cross, move.x, move.y, move.animation.currentScale);
        } else if (move.type == CIRCLE) {
            drawMove(circle, move.x, move.y, move.animation.currentScale);
        }
    }
}

void InitGame(void) {
    // During development, align the screen to the right edge of the screen
    SetWindowPosition(1100, 300);

    circle = LoadTexture("resources/textures/circle.png");
    cross = LoadTexture("resources/textures/cross.png");

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            board[x][y] = EMPTY;
        }
    }
}

bool isMoveAvailable() {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (board[x][y] == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

void AIMove() {
    int aiMoveX, aiMoveY;

    do {
        aiMoveX = GetRandomValue(0, 2);
        aiMoveY = GetRandomValue(0, 2);
    } while (board[aiMoveX][aiMoveY] != EMPTY);

    board[aiMoveX][aiMoveY] = CROSS;
    Move aiMove = { CROSS, aiMoveX, aiMoveY };
    initializeMoveAnimation(&aiMove);
    moves[moveCount++] = aiMove;
}

void UpdateGame(void) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();

        int boardX = (mousePos.x - 80) / 80;
        int boardY = (mousePos.y - 80 - HUD_GAP) / 80;

        if (boardX >= 0 && boardX < 3 && boardY >= 0 && boardY < 3) {
            if (board[boardX][boardY] == EMPTY) {
                board[boardX][boardY] = CIRCLE;
                Move playerMove = { CIRCLE, boardX, boardY };
                initializeMoveAnimation(&playerMove);
                moves[moveCount++] = playerMove;

                // Make the AI move after the player move, if there's space available
                if (isMoveAvailable()) {
                    AIMove();
                }
            }
        }
    }

    updateAnimations(moves, moveCount);
}

// Draw game (one frame)
void DrawGame(void) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    drawHud();
    drawBoard();
    drawMoves();

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