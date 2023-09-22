#include "animations.h"
#include "reasings.h"

float targetScale = 1.0f;
float duration = 1.0f;
float startScale = .5f;

void updateAnimations(Move moves[], int moveCount) {
    if (moveCount > 0) {
        Move *lastMove = &moves[moveCount - 1];
        lastMove->animation.currentTime += GetFrameTime();

        if (lastMove->animation.currentTime < duration) {
            float t = lastMove->animation.currentTime / duration;
            lastMove->animation.currentScale = startScale + (targetScale - startScale) * EaseElasticOut(t, 0.0f, 1.0f, 1.0f);
        } else {
            lastMove->animation.currentScale = targetScale;
        }
    }
}

void initializeMoveAnimation(Move *move) {
    move->animation.currentScale = startScale;
    move->animation.currentTime = 0.0f;
}

void resetAnimation(Move *move) {
    move->animation.currentTime = 0.0f;
    move->animation.currentScale = startScale;
}