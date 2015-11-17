#include "Render.h"

Render::Render(){}

Render::~Render(){}

void Render::SetEntity(Entity* entity)
{
    m_entity = entity;
}


void Render::Draw(SDL_Surface * surf){
    m_entity->draw(surf);
}
