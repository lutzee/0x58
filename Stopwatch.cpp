#include "Stopwatch.h"

Uint32 Stopwatch::stop()
{
    if(running)
    {
        elapsed += SDL_GetTicks() - startTime;
        running = false;
    }
    return elapsed;
}

Uint32 Stopwatch::read()
{
    if(running)
    {
        Uint32 now = SDL_GetTicks();
        elapsed += now - startTime;
        startTime = now;
    }
    return elapsed;
}
