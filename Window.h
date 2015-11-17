#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <time.h>

/**
*   The console window class. Combines console behaviour with turtle graphics and enables rendering
*   to an SDL background surface.
*/
class Window
{
private:

    SDL_Surface * screen;
    SDL_Surface * backg;
    TTF_Font * font;
    SDL_Rect winRect;
    SDL_Event event;
    SDL_Color backColour;
    SDL_Color textFg;
    std::string mtext;

    bool got;
    char last;
    
public:

    /**
    *   Builds a new console window. Width and height should represent an appropriate video mode if specified
    *   i.e. 1024 x 768, 800 x 600, 640 x 480 etc
    *
    *   @param  width       The width of the console in pixels, default 1024
    *   @param  height      The height of the console in pixels, default 768
    *   @param  fontPitch   The pitch of the console font, 16
    */
    Window(int width=1024, int height=768);

    /**
    *   Reads a single character from the keyboard.
    *   Main usage in waiting for user keypress since return variable may be ignored
    *   @return The first key pressed by the user
    */
    char getchar();

    /**
    *   Sets the text area text
    */
    void setText(std::string);

    /**
    *   Returns the console background as an SDL_Surface. Enables fun with graphics!
    *   @return A pointer to the background surface
    */
    SDL_Surface * getGraphics(){return screen;}

    /**
    *   Redraws the text area
    */
    void renderTextArea();
    
    virtual ~Window();
} ;

#endif // WINDOW_H_INCLUDED
