#include "animations.h"
#include "reasings.h"

float targetScale = 1.0f;
float duration = 1.0f;
float startScale = .5f;

void updateAnimations(Move moves[], int moveCount) {
    for (int i = 0; i < moveCount; i++) {
        if (moves[i].animation.shouldAnimate) {
            moves[i].animation.currentTime += GetFrameTime();
            if (moves[i].animation.currentTime < duration) {
                float t = moves[i].animation.currentTime / duration;
                moves[i].animation.currentScale = startScale + (targetScale - startScale) * EaseElasticOut(t, 0.0f, 1.0f, 1.0f);
            } else {
                moves[i].animation.currentScale = targetScale;
                moves[i].animation.shouldAnimate = false; // Animation is complete
            }
        }
    }
}

void initializeMoveAnimation(Move* move) {
    move->animation.currentScale = startScale;
    move->animation.currentTime = 0.0f;
    move->animation.shouldAnimate = true; // Add this line
}