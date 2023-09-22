#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "raylib.h"

// Set the initial scale factor and the target scale factor
extern float currentScale;
extern float targetScale;

// Easing parameters
extern float duration;
extern float currentTime;
extern float startScale;

// Function to update animations
void updateAnimations(void);

#endif // ANIMATIONS_H
