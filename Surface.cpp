#include "Surface.h"

Surface::Surface(){}

SDL_Surface * Surface::onLoad(std::string File){
    SDL_Surface * surfTemp = NULL;
    SDL_Surface * surfReturn = NULL;

    if((surfTemp = SDL_LoadBMP(File.c_str())) == NULL){
        return NULL;
    }

    surfReturn = SDL_DisplayFormat(surfTemp);

    SDL_FreeSurface(surfTemp);

    return surfReturn;
}

bool Surface::onDraw(SDL_Surface* surfDest, SDL_Surface* surfSrc, int X, int Y) {
    if(surfDest == NULL || surfSrc == NULL) {
        return false;
    }

    SDL_Rect destRect;

    destRect.x = X;
    destRect.y = Y;

    SDL_BlitSurface(surfSrc, NULL, surfDest, &destRect);

    return true;
}

bool Surface::onDraw(SDL_Surface* surfDest, SDL_Surface* surfSrc, float X, float Y, int X2, int Y2, int W, int H) {
    if(surfDest == NULL || surfSrc == NULL) {
        return false;
    }

    SDL_Rect destRect;

    destRect.x = X;
    destRect.y = Y;

    SDL_Rect srcRect;

    srcRect.x = X2;
    srcRect.y = Y2;
    srcRect.w = W;
    srcRect.h = H;

    SDL_BlitSurface(surfSrc, &srcRect, surfDest, &destRect);

    return true;
}

bool Surface::Transparent(SDL_Surface* surfDest, int R, int G, int B) {
    if(surfDest == NULL) {
        return false;
    }

    SDL_SetColorKey(surfDest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surfDest->format, R, G, B));

    return true;
}

