
#include "Game.h"

//initialising the vector
std::vector<Entity*> Game::EntityList;


/**
*   Constructor for the Game Class
*/
Game::Game(){
    displaySurface = NULL;
    running = true;
    paused = false;
    timeQueued = 0;

    scorestring = "";

    score = 0;
    theend = false;
    maxEntities = 10;
    currentEntities = 0;
}

/**
*   Destructor for the Game Class
*/

Game::~Game(){

}

/**
*   Gets called when the game is started, moves everything out of main
*   When this function exits the game exits
*/

int Game::Run(){
    win = new Window(1280,760);

    //The gmae timers start and end
    Stopwatch time;

    //Calls the init function to initilise everything
    if(init() == false){
        return -1;
    }

    //Gets the surface of the screen
    displaySurface = win->getGraphics();

    //initialises SDLs event handler
    SDL_Event event;

    //Gets a timestamp for calculating delta times between ticks
    double oldTime = GetTime();

    //Start the timer
    time.start();

    //The main game loop
    while(running){
        //initialises the player entity velocity to 0,
        //this resets velocity on each loop to prevent the player from carrying
        // on in one direction after the movement keys have stopped being pressed
        entity.velocityX = 0;
        entity.velocityY = 0;

        //Checks to see if an event has occured,
        while(SDL_PollEvent(&event)){
            onEvent(&event);
        }

        //Calculates the delta time for dealing with the tick since last loop
        const double newTime = GetTime();
        double dt = newTime - oldTime;
        oldTime = newTime;

        //Deals with all game state changes
        loop(dt);

        //deals with all rendering
        win->setText(" Score: " + std::to_string(score) + "       Time Left: " + std::to_string(60-(int)(time.read()/1000)) + "s");
        render();
        if(time.read() > 60000 && !theend){
            theend = true;
            time.stop();
            std::ofstream score;
            score.open("score.txt", std::ios::ate | std::ios::out);
            score << "Last score: " << this->score << "\n" << scorestring;
            score.flush();
            score.close();
        running=false;

        while(SDL_WaitEvent(&event)){
            if(event.key.keysym.sym == SDLK_RETURN)
                break;
        }
    }
}
    //this is only called when the game is exiting, makes sure the game exits cleanly with all memory cleared correctly
    cleanUp();

    return 0;
}



/**
*   Loads all the graphics and sets some initial conditions in SDL such as allowing for keys held down to retrigger events
*/

bool Game::init(){
    //initialises the random seed using the current timestamp
    srand(time(NULL));
    //Loads the background image
    if(background.onLoad("./images/background.bmp", 1280,720,1)==false){
        return false;
    }

    //loads the player image
    if(entity.onLoad("./images/player.bmp", 64,64,8)==false){
        return false;
    }
    //pushes the background entity to the back of the Entity vector
    EntityList.push_back(&background);

    //pushes the player entity to the back of the Entity vector
    EntityList.push_back(&entity);

    //enables repeat keys so movement keys can be held down
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    //returns true if initilisation was successful
    return true;
}

/**
*   Deals with any events that occur
*
*   @param SDL_Event event The pointer to the instance of the event handler
*/

void Game::onEvent(SDL_Event * event){

    //Deals with pressing the X button on the window causing a quit
    if(event->type == SDL_QUIT) {
        running = false;
    }

    //key Left control to pause the game
    if(event->type == SDL_KEYDOWN){
        if(event->key.keysym.sym == SDLK_LCTRL){
            paused = !paused;
        }
    }

    //key Q to quit the game also
    if(event->type == SDL_KEYDOWN) {
        if(event->key.keysym.sym == SDLK_q) {
            running = false;
        }
    }

    //Gets a snapshot of the current keyboard state
    Uint8* keystate = SDL_GetKeyState(NULL);
    {
        //key right arrow or D to move the player right
        if(keystate[SDLK_RIGHT] || keystate[SDLK_d]){
            entity.AccelerationX+=200.0;
        }
        //key left arrow or A to move the player left
        if(keystate[SDLK_LEFT] || keystate[SDLK_a]){
            entity.AccelerationX-=200.0;
        }
        //key up arrow or W to move the player up
        if(keystate[SDLK_UP] || keystate[SDLK_w]){
            entity.AccelerationY-=200.0;
        }
        //key Down arrow or S to move the player down
        if(keystate[SDLK_DOWN] || keystate[SDLK_s]){
            entity.AccelerationY+=200.0;
        }
    }
}

/**
*   The main loop function for the game, all gamestate changes occur here.
*
*   @param double dt the deltatime for
*/

void Game::loop(double dt){
    //checks if the game is paused, rendering can still occur even if the game is paused this way
    if(!paused){
        //queues some time length to calculate the movement under
        timeQueued += dt;
        //while time queued is greater than a tick do..
        while(timeQueued > (1.0/500)) {
            //remove 1 tick length from time queue
            timeQueued -= (1.0/500);
            //Call the loop function for each entity in the entity vector
            for(int i = 0; i < EntityList.size(); ++i) {
                if(!EntityList[i]) continue;
                EntityList[i]->loop(1.0/50);
            }
        }

        //spawns a fresh set of enemy entities
        if(currentEntities < maxEntities){
            spawnEntity(new EntityEnemy());
            currentEntities +=1;
        }

        //check for any collisions with the player
        for( int i = 1; i < EntityList.size(); ++i){
            //creates an Axis-Aligned bounding box for the first entity
            AABB entityA_AABB;
            EntityList[i]->getAABB(entityA_AABB);
            //checks for collisions with every entity after the one being checked
            for(int j = i + 1; j < EntityList.size(); ++j){
                AABB entityB_AABB;
                EntityList[j]->getAABB(entityB_AABB);

                //if the first entity is a player then..
                if(EntityList[i]->isPlayer()){
                    //checks for a collision
                    if(AABBinstersect(entityA_AABB, entityB_AABB)){
                        //tells the entity to despawn
                        EntityList[j]->despawn();
                        // debugging printf("Collision! a.x: %f a.y: %f b.x: %f b.y: %f i: %i j: %i player1: %i player2: %i\n", entityA_AABB.p1.x, entityA_AABB.p1.y, entityB_AABB.p1.x, entityB_AABB.p1.y, i , j, EntityList[i]->isPlayer(), EntityList[j]->isPlayer());
                        score++;
                    }
                }

                //if the first entity is a player then..
                if(EntityList[j]->isPlayer()){
                    //checks for a collision
                    if(AABBinstersect(entityA_AABB, entityB_AABB)){
                        //tells the entity to despawn
                        EntityList[i]->despawn();
                        // debugging printf("Collision! a.x: %f a.y: %f b.x: %f b.y: %f i: %i j: %i player: %i player2: %i\n", entityA_AABB.p1.x, entityA_AABB.p1.y, entityB_AABB.p1.x, entityB_AABB.p1.y, i , j, EntityList[i]->isPlayer(), EntityList[j]->isPlayer());
                        score++;
                    }
                }
            }
        }
    }

    //checks all entities to see if they are dead and actually despawns them now
        for(int i = 1; i < EntityList.size(); ++i){
            if(EntityList[i]->isDead()){
                //deletes the instance of the entity
                delete EntityList[i];
                //removed the null pointer from the vector
                EntityList.erase(EntityList.begin() + i);
                //decrements the current entities
                currentEntities--;
            }
        }
        if(entity.AccelerationX==0){

        } else if(entity.AccelerationX<0){
            entity.AccelerationX+=50.0;
        } else {
            entity.AccelerationX-=50.0;
        }
        if(entity.AccelerationY==0){

        } else if(entity.AccelerationY<0){
            entity.AccelerationY+=50.0;
        } else {
            entity.AccelerationY-=50.0;
        }
    }

/**
*   Deals with all the rendering that occurs
*/

void Game::render(){
    //draws the screen to black every frame
    SDL_Rect rect;
    rect.x =0;
    rect.y = 0;
    rect.w = 1280;
    rect.h = 720;
    SDL_FillRect(displaySurface, &rect, (displaySurface->format,0,0,0));

    //Calls the draw function of every entity
    for(int i = 0; i < EntityList.size(); ++i) {
        if(!EntityList[i]) continue;
        EntityList[i]->draw(displaySurface);
    }

    //Flips the two surface buffers to actually display the changes
    SDL_Flip(displaySurface);
    win->renderTextArea();
}

/**
*   Deals with exiting the game, cleans up any allocated memory
*/
void Game::cleanUp(){
    //calls the cleanup function of every entity
    for(int i = 0; i < EntityList.size(); ++i) {
    if(!EntityList[i]) continue;

    EntityList[i]->onCleanup();
    }

    //clears the vector of all pointers
    EntityList.clear();

    //frees the surface of the screen
    SDL_FreeSurface(displaySurface);

    //this goes out of scope and the progam closes calling any nessasary destructors
}

/**
*   Deals with spawning of new enemy entities
*
*   @param EntityEnemy entity pointer to a new entity to be spawned
*/
bool Game::spawnEntity(EntityEnemy * entity){
    //loads the entitys image
    if(entity->onLoad("./images/entity.bmp", 32,32,8)==false){
        return false;
    }

    //pushes the entity to the back of the vector
    EntityList.push_back(entity);
    return true;
}

