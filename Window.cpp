#include <sstream>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "Window.h"

Window::Window(int width, int height)
{
    winRect.x = 0;
    winRect.y = 0;
    winRect.w = width;
    winRect.h = height;

    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
      
    if(SDL_GetVideoInfo()->hw_available == 1)
        screen = SDL_SetVideoMode( width, height, 32, SDL_OPENGL );
    else
        screen = SDL_SetVideoMode( width, height, 32, SDL_SWSURFACE | SDL_DOUBLEBUF );

    SDL_WM_SetCaption("0x58",NULL);

    SDL_EnableUNICODE(1);

    backg = SDL_CreateRGBSurface( 0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    
    font = TTF_OpenFont( "./fonts/Roboto-Regular.ttf", 32);
    textFg = {255,255,255,0};
}

Window::~Window()
{
    TTF_CloseFont(font);
    SDL_FreeSurface(backg);
    SDL_FreeSurface(screen);
    SDL_EnableUNICODE(0);
    SDL_Quit();
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

void Window::setText(std::string text)
{
    mtext = text;
}

void Window::renderTextArea()
{
    SDL_Rect textLocation = {0,720,winRect.w,40};
    SDL_FillRect(screen, &textLocation, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_Surface * textArea = TTF_RenderText_Solid( font, mtext.c_str(), textFg );
    SDL_BlitSurface(textArea,NULL,screen,&textLocation);
    SDL_FreeSurface(textArea);
}
