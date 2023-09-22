#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "raylib.h"

typedef struct {
    float currentScale;
    float currentTime;
} AnimationState;

typedef struct {
    int type; // CROSS or CIRCLE
    int x;
    int y;
    AnimationState animation;
} Move;

extern void initializeMoveAnimation(Move *move);
extern void updateAnimations(Move moves[], int moveCount);
extern void resetAnimation(Move *move);

#endif
