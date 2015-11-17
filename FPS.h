#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED

#include <SDL/SDL.h>

class FPS {
    public:
        static FPS fpsControl;

    private:
        int OldTime;
        int LastTime;

        float SpeedFactor;

        int NumFrames;
        int Frames;

    public:
        FPS();

        void loop();

    public:
        int getFPS();

        float getSpeedFactor();
};


#endif // FPS_H_INCLUDED
