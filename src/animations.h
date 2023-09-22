#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "raylib.h"

typedef struct {
    float currentTime;
    float currentScale;
    bool shouldAnimate;
} Animation;

typedef struct {
    int type; // CROSS or CIRCLE
    int x;
    int y;
    Animation animation;
} Move;

extern void initializeMoveAnimation(Move *move);
extern void updateAnimations(Move moves[], int moveCount);

#endif
