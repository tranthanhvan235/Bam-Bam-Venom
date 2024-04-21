#pragma once

#include "const.h"
#include "Timer.h"
#include "Res.h"
#include "Collision.h"

#define MAX_IMMORTAL_TIME 500

class Snake
{
public:
    // Constructor and destructor
    Snake();
    ~Snake();

    int SNAKEWIDTH = 250 * 1.5, SNAKEHEIGHT = 250 * 1.5;
    
    void reset();
    void handleEventSnake(SDL_Event &e);
    void updateGame();

    Collision getCol();
    
    void render(bool isPaused);

    //Dir
    bool goingUp = false, goingDown = false;

    //Current position
    int sPosX = SCREEN_WIDTH - 220*1.5, sPosY = SCREEN_HEIGHT - 350*1.5;

    //Velocity
    int sVelX, sVelY;

    int velFrame = 1, frame;
    
    int immortalTime = 0;
    bool isImmortal();
    
private:
    Texture snake;
    SDL_Rect snakeClips[5];
    Timer timer;
    Collision snakeCol[5];
};