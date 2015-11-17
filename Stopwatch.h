#ifndef STOPWATCH_H_INCLUDED
#define STOPWATCH_H_INCLUDED

#include <SDL/SDL.h>
#include <time.h>

/**
*	A stopwatch class to enable timing (for animation etc)
*/
class Stopwatch
{
    Uint32 startTime, elapsed;
    bool running;
    public:
    /**
    *   Creates a stopwatch
    */
    Stopwatch():startTime(0), elapsed(0), running(false){}

    /**
    *   Starts the watch (adds to current time if watch has not been reset
    */
    void start(){if(running) return; startTime = SDL_GetTicks(); running = true;}

    /**
    *   Stops the watch (does not reset the time)
    *   @return the time on the watch
    */
    Uint32 stop();

    /**
    *   Reads the watch (does not stop)
    *   @return the current time on the watch
    */
    Uint32 read();

    /**
    *   Resets time to zero
    */
    void reset(){startTime = SDL_GetTicks(); elapsed = 0;}
};

#endif // STOPWATCH_H_INCLUDED