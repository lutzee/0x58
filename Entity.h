#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <vector>
#include <string>
#include "Animation.h"
#include "util.h"
#include "Surface.h"
#include "Animation.h"
#include "time.h"
#include "util.h"

class Entity{
protected:
    //Entity animation controller
    Animation animation;

    //Entity render surface
    SDL_Surface* entitySurface;

public:
    int type;

    bool dead;
    int flags;

private:
    //Entity position
    float X;
    float Y;

    //Entity size
    int Width;
    int Height;
public:
    //Entity velocity
    int velocityX;
    int velocityY;
    double AccelerationX;
    double AccelerationY;

    //Current animation frame
    int animationState;

public:
    //Entity constructor and destructor
    Entity();
    virtual ~Entity();

public:
    //Loads the Entities image and size
    virtual bool onLoad(std::string File, int Width, int Height, int MaxFrames);

    //Function to deal with movement and collisions
    virtual void loop(const double dt);

    //Draws the entity
    virtual void draw(SDL_Surface * surface);

    //Removes the entity from the vector and frees the memory
    virtual void onCleanup();

    //Deals with anything after collisions, called when two entites collide
    //virtual void onCollision(Entity* entity);

    virtual void getAABB(AABB &aabb);

    void despawn(){dead = true;}


public:
    float getX(){return X;}
    float getY(){return Y;}

    void setX(float mX){X=mX;}
    void setY(float mY){Y=mY;}

    virtual bool isPlayer(){return false;}
    bool isDead(){return dead;}
};


class EntityPlayer : public Entity{
protected:
    //Entity animation controller
    Animation animation;

    //Entity render surface
    SDL_Surface* entitySurface;

    int type;

private:
    //Entity position
    float X;
    float Y;
    //Entity size
    int Width;
    int Height;
public:
    EntityPlayer();
    ~EntityPlayer();
    double velocityX;
    double velocityY;

    void setVelocityX(double velocity){velocityX=velocity;}
    void setVelocityY(double velocity){velocityY=velocity;}

    bool onLoad(std::string File, int Width, int Height, int MaxFrames);
    void loop(const double dt) ;
    void draw(SDL_Surface * surf);
    void onCleanup();
    void despawn(){dead = true;}
    void getAABB(AABB &aabb);
    bool isPlayer(){return true;}

};
class EntityEnemy : public Entity{
protected:
    //Entity animation controller
    Animation animation;

    //Entity render surface
    SDL_Surface* entitySurface;

private:
    //Entity position
    float X;
    float Y;

    //Entity size
    int Width;
    int Height;

    int type;

    int random;

    bool dead;
public:
    EntityEnemy();
    ~EntityEnemy();

    double velocityX;
    double velocityY;

    void setVelocityX(double velocity){velocityX=velocity;}
    void setVelocityY(double velocity){velocityY=velocity;}

    bool onLoad(std::string File, int Width, int Height, int MaxFrames);
    void loop(const double dt) ;
    void draw(SDL_Surface * surf);
    void onCleanup();
    void despawn(){dead = true;}
    void getAABB(AABB &aabb);
    bool isPlayer(){return false;}
};
#endif // ENTITY_H_INCLUDED
