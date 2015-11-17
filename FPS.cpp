#include "FPS.h"

FPS FPS::fpsControl;

FPS::FPS() {
    OldTime     = 0;
    LastTime    = 0;

    SpeedFactor    = 0;

    Frames      = 0;
    NumFrames   = 0;
}

void FPS::loop() {
    if(OldTime + 1000 < SDL_GetTicks()) {
        OldTime = SDL_GetTicks();

        NumFrames = Frames;

        Frames = 0;
    }

    SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * 32.0f;

    LastTime = SDL_GetTicks();

    Frames++;
}

int FPS::getFPS() {
    return NumFrames;
}

float FPS::getSpeedFactor() {
    return SpeedFactor;
}
