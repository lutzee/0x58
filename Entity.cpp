#include "Entity.h"
#include "Surface.h"
#include "Animation.h"
#include "time.h"
#include "util.h"
#include <cstdlib>

Entity::Entity(){

    //Initialises the entities surface to null until an image is loaded
    entitySurface = NULL;

    //Initialises the entities initial position to 0,0
    X=Y=0.0f;

    dead=false;

    //Initialises the velocity to 0
    velocityX = velocityY = 0;
    AccelerationX = AccelerationY = 0;
    //Initialises the size to 0
    Width=Height=0;

    //Initialises the animation to the first frame
    animationState = 0;
}

Entity::~Entity(){
    onCleanup();
}

/**
*  Loads a file and size into the entity being instantiated
*
*  @param File The pointer to the file to be loaded
*  @param Width The width of the entity
*  @param Height The height of the entity
*  @param MaxFrames The amount of frames the entity animates through
*  @return Returns true if everything completed, false if not, false is an error and crashes
*/

bool Entity::onLoad(char* File, int Width, int Height, int MaxFrames) {
    // If the file is null return false, this is an error and will cause a crash
    if((entitySurface = Surface::onLoad(File)) == NULL) {
    return false;
    }

    //Sets the transparent pixel to #FF00FF

    Surface::Transparent(entitySurface, 255, 0, 255);

    //sets the Width and height inputted to the actual width for the instantiated entity
    this->Width = Width;
    this->Height = Height;

    //sets the max frames inputted to the actual max frames for the instantiated entity
    animation.maxFrames = MaxFrames;

    return true;
}

/**
 *  Any game state changes to the entities occur here
 *
 * @param dt The delta time since the last call
 */

void Entity::loop(const double dt){
    //to be filled by subclass
}

/**
 *  Draws the entity to its surface
 *
 * @param surf The surface of the screen
 */

void Entity::draw(SDL_Surface * surf){
    if(entitySurface == NULL || surf == NULL) return;
    Surface::onDraw(surf, entitySurface,X,Y,animationState * Width, animation.getCurrentFrame() * Height, Width, Height);
}

/**
 *  Clears the entity after it is not needed
 */

void Entity::onCleanup(){
    if(entitySurface){
        SDL_FreeSurface(entitySurface);
    }
    entitySurface = NULL;
}

void Entity::getAABB(AABB &aabb){
    aabb.p1.x = X;
    aabb.p1.y = Y;
    aabb.p2.x = X+Width;
    aabb.p2.y = Y+Height;
}

EntityPlayer::EntityPlayer(){

    //Initialises the entities surface to null until an image is loaded
    entitySurface = NULL;

    //Initialises the entities initial position to 0,0
    X=Y=0.0f;

    dead=false;
    //Initialises the velocity to 0
    velocityX = velocityY = 0;

    //Initialises the size to 0
    Width=Height=0;

    //Initialises the animation to the first frame
    animationState = 0;
}

EntityPlayer::~EntityPlayer(){
    onCleanup();
}

bool EntityPlayer::onLoad(char* File, int Width, int Height, int MaxFrames){
    // If the file is null return false, this is an error and will cause a crash
    if((entitySurface = Surface::onLoad(File)) == NULL) {
    return false;
    }

    //Sets the transparent pixel to #FF00FF

    Surface::Transparent(entitySurface, 255, 0, 255);

    //sets the Width and height inputted to the actual width for the instantiated entity
    this->Width = Width;
    this->Height = Height;

    //sets the max frames inputted to the actual max frames for the instantiated entity
    animation.maxFrames = MaxFrames;

    return true;
}

void EntityPlayer::loop(const double dt){

    velocityX = AccelerationX * dt;
    velocityY = AccelerationY * dt;
    //Moves the entity a certain amount compared with the delta time of before and after the loop
    X += velocityX * dt;
    Y += velocityY * dt;
    if(X < 0)
        X = 0;
    if(X > 1280 - Width)
        X = 1280 - Width;
    if(Y < 0)
        Y=0;
    if(Y > 720 - Height)
        Y = 720 - Height;
    animation.animate();
}

void EntityPlayer::draw(SDL_Surface * surf){
    if(entitySurface == NULL || surf == NULL) return;
        Surface::onDraw(surf, entitySurface,X,Y,animationState * Width, animation.getCurrentFrame() * Height, Width, Height);
}

void EntityPlayer::onCleanup(){
    if(entitySurface){
        SDL_FreeSurface(entitySurface);
    }
    entitySurface = NULL;
}

void EntityPlayer::getAABB(AABB &aabb){
    aabb.p1.x = X;
    aabb.p1.y = Y;
    aabb.p2.x = X+Width;
    aabb.p2.y = Y+Height;
}

EntityEnemy::EntityEnemy(){
    //Initialises the entities surface to null until an image is loaded
    entitySurface = NULL;


    //init_rand(time(NULL));

    //Initialises the entities initial position to 0,random
    X=rand()%(1280-80);
    Y=rand()%(720-80);
    printf("X: %f Y: %f \n", X, Y);
    dead=false;
    random = getRandom();
    //Initialises the velocity to 0
    velocityX =10+rand()%10 * random;
    velocityY =10+rand()%10 * random;
    printf("velX: %fvelY: %f\n", velocityX, velocityY);

    //Initialises the size to 0
    Width=Height=0;

    //Initialises the animation to the first frame
    animationState = 0;
}

EntityEnemy::~EntityEnemy(){
    onCleanup();
}

bool EntityEnemy::onLoad(char* File, int Width, int Height, int MaxFrames){
    // If the file is null return false, this is an error and will cause a crash
    if((entitySurface = Surface::onLoad(File)) == NULL) {
    return false;
    }

    //Sets the transparent pixel to #FF00FF

    Surface::Transparent(entitySurface, 255, 0, 255);

    //sets the Width and height inputted to the actual width for the instantiated entity
    this->Width = Width;
    this->Height = Height;

    //sets the max frames inputted to the actual max frames for the instantiated entity
    animation.maxFrames = MaxFrames;

    return true;
}


void EntityEnemy::loop(const double dt){
    //Moves the entity a certain amount compared with the delta time of before and after the loop

    X += velocityX * dt;
    Y += velocityY * dt;
    if(X < 0){
        velocityX *= -1;
            X = 0;
    }
    if(X > 1280 - Width){
        X = 1280 - Width;
        velocityX *= -1;
    }
    if(Y < 0){
        Y=0;
        velocityY *= -1;
    }
    if(Y > 720 - Height){
        Y = 720 - Height;
        velocityY *= -1;
    }

    animation.animate();
}

void EntityEnemy::draw(SDL_Surface * surf){
    if(entitySurface == NULL || surf == NULL) return;
        Surface::onDraw(surf, entitySurface,X,Y,animationState * Width, animation.getCurrentFrame() * Height, Width, Height);
}

void EntityEnemy::onCleanup(){
    if(entitySurface){
        SDL_FreeSurface(entitySurface);
    }
    entitySurface = NULL;
}


void EntityEnemy::getAABB(AABB &aabb){
    aabb.p1.x = X;
    aabb.p1.y = Y;
    aabb.p2.x = X+Width;
    aabb.p2.y = Y+Height;
}
