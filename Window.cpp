#include <sstream>
#include <cstdlib>
#include <math.h>
#include "Window.h"

Window::Window(int width, int height, int fontpitch)
{
    winRect.x = 0;
    winRect.y = 0;
    winRect.w = width;
    winRect.h = height;

    SDL_Init( SDL_INIT_EVERYTHING );
      
    if(SDL_GetVideoInfo()->hw_available == 1)
        screen = SDL_SetVideoMode( width, height, 32, SDL_OPENGL );
    else
        screen = SDL_SetVideoMode( width, height, 32, SDL_SWSURFACE | SDL_DOUBLEBUF );

    SDL_WM_SetCaption("0x58",NULL);

    SDL_EnableUNICODE(1);

    backg = SDL_CreateRGBSurface( 0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
}

Window::~Window()
{
    SDL_FreeSurface(backg);
    SDL_FreeSurface(screen);
    SDL_EnableUNICODE(0);
    SDL_Quit();
}

void Window::applySurface( int x, int y, SDL_Surface* src, SDL_Surface* dest, SDL_Rect* clip)
{
    SDL_Rect r;

    r.x = x;
    r.y = y;

    SDL_BlitSurface(src, clip, dest, &r);
}

char Window::getchar()
{
    if(got == true)
    {
        got = false;
        return last;
    }
    bool quit = false;
    char input;
    while(!quit)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_KEYDOWN)
        {
            input = (char) event.key.keysym.unicode;
        }
    }
    return input;
}


void Window::render()
{
    SDL_FillRect(screen, &winRect, 0xFF000000);
    applySurface( 0, 0, backg , screen );
    SDL_Flip(screen);
}

