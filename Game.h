#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Window.h"
#include "Entity.h"
#include "Render.h"
#include "util.h"
#include "time.h"
#include "Stopwatch.h"

#include <fstream>
#include <iostream>
#include <string>
#include <SDL/SDL.h>

//forward declaration of the entity class
class Entity;

/**
*   The game class, this is the main class for the game and deals with executing the main stages of the game
*/


class Game{
private:
    bool running;
    bool theend;
    bool paused;

    int maxEntities;
    int currentEntities;

    int score;

    std::string scorestring;

    double timeQueued;

    Entity background;
    EntityPlayer entity;
    
    Window *win;
    SDL_Surface* displaySurface;
public:
    /**
    *   Builds the structure for the game
    */
    Game();

    ~Game();

    /**
    *   Vector for storing all the entities
    */
    static std::vector<Entity*> EntityList;


public:
    /**
    *   Gets called when the game is started, moves everything out of main
    *   When this function exits the game exits
    */
    int Run();

    /**
    *   Loads all the graphics and sets some initial conditions in SDL such as allowing for keys held down to retrigger events
    */
    bool init();

    /**
    *   Deals with any events that occur
    *
    *   @param SDL_Event event The pointer to the instance of the event handler
    */
    void onEvent(SDL_Event* event);

    /**
    *   The main loop function for the game, all gamestate changes occur here.
    *
    *   @param double dt the deltatime for
    */
    void loop(double dt);

    /**
    *   Deals with all the rendering that occurs
    */

    void render();

    /**
    *   Deals with exiting the game, cleans up any allocated memory
    */
    void cleanUp();

    /**
    *   Deals with spawning of new enemy entities
    *
    *   @param EntityEnemy entity pointer to a new entity to be spawned
    */
    bool spawnEntity(EntityEnemy * entity);

};


#endif // GAME_H_INCLUDED
