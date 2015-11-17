#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include <SDL/SDL.h>
#include <string>

class Surface{
public:
    Surface();
    ~Surface();

public:
    /**
    *   Takes a pointer to a file and loads it onto a surface
    *
    *   @param char* File File to load onto the surface
    */
    static SDL_Surface* onLoad(std::string File);

    /**
    *   Draws the specified surface onto the game surface
    *
    *   @param surfDest The surface to be drawn on to
    *   @param surfSrc The surface to be drawn
    *   @param X the X coordinate of where to draw the surfSrc on the surfDest
    *   @param Y the Y coordinate of where to draw the surfSrc on the surfDest
    */
    static bool onDraw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int x, int y);

    /**
    *   Draws the specified surface onto the game surface
    *
    *   @param surfDest The surface to be drawn on to
    *   @param surfSrc The surface to be drawn
    *   @param X the X coordinate of where to draw the surfSrc on the surfDest
    *   @param Y the Y coordinate of where to draw the surfSrc on the surfDest
    *   @param X2 the X coordinate of location in the file from with to draw from
    *   @param Y2 the XY coordinate of location in the file from with to draw from
    *   @param W the Width of the area to draw from the file
    *   @param H the Height of the area to draw from the file
    */
    static bool onDraw(SDL_Surface* surfDest, SDL_Surface* surfSrc, float X, float Y, int X2, int Y2, int W, int H);

    /**
    *   Takes a colour in to replace with transparent pixels
    *
    *   @param surfDest The surface to apply the transparency settings to
    *   @param R the value for the red colour range
    *   @param G the value for the green colour range
    *   @param B the value for the blue colour range
    */
    static bool Transparent(SDL_Surface* surfDest, int R, int G, int B);
};

#endif // SURFACE_H_INCLUDED
