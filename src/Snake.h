#pragma once

#include "Fruit.h"
#include "board.h"
#include "Collision.h"

class Snake
{
public:
    // Constructor and destructor
    Snake();
    ~Snake();

    int SNAKEWIDTH = 250 * 1.5, SNAKEHEIGHT = 250*1.5;

    void handleEventSnake(SDL_Event &e);
    void updateGame();

    int checkCollision();
    
    void render(bool isPaused);

    //Dir
    bool goingUp = false, goingDown = false;

    //Current position
    int sPosX = SCREEN_WIDTH - 220*1.5, sPosY = SCREEN_HEIGHT - 350*1.5;

    //Velocity
    int sVelX, sVelY;

    int frame = 0, velFrame = 1;
    
    Texture snake;
    SDL_Rect snakeClips[5];
    
    Timer time;
    Timer timer;

    Fruit fruit;
    Board board;
    Collision snakeCol[5];
};