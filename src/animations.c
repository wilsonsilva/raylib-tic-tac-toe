#include "animations.h"
#include "raylib.h"
#include "reasings.h"

// Set the initial scale factor and the target scale factor
float currentScale = .5f;
float targetScale = 1.0f;

// Easing parameters
float duration = 1.0f; // Animation duration in seconds
float currentTime = 0.0f;
float startScale = .5f;

void updateAnimations() {
    currentTime += GetFrameTime();

    // Calculate the next scale factor using the EaseElasticOut easing function
    if (currentTime < duration)
    {
        float t = currentTime / duration;
        currentScale = startScale + (targetScale - startScale) * EaseElasticOut(t, 0.0f, 1.0f, 1.0f);
    }
    else
    {
        currentScale = targetScale;
    }
}
