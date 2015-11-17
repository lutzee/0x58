#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <SDL/SDL.h>

class Animation{
private:
    int currentFrame;
    int frameInc;
private:
    int frameRate;
    long oldTime;

public:
    int maxFrames;

    bool oscilate;

public:
    Animation();

    /**
    *   Deals with changing the frame
    */
    void animate();

public:
    /**
    *   Sets the framerate
    *
    *   @param rate Framerate to be set
    */
    void setFrameRate(int rate);

    /**
    *   Sets the current framee
    *
    * @param frame the frame index to be set
    */
    void setCurrentFrame(int Frame);

    /**
    *   Returns the current frame
    */
    int getCurrentFrame();
};


#endif // ANIMATION_H_INCLUDED
