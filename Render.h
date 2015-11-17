#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "Game.h"
#include "Entity.h"
#include <SDL/SDL.h>

class Entity;

class Render{
public:
    Render();
    ~Render();
    void SetEntity(Entity* entity);
    void Draw(SDL_Surface * surf);
private:
    Entity* m_entity;
};

#endif // RENDER_H_INCLUDED
