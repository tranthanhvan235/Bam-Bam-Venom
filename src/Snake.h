#pragma once

#include "Fruit.h"
#include "wood.h"
#include "Collision.h"

#include <vector>

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

    void randLevel();

    int checkCollision();
    
    void render(bool isPaused);

    //Dir
    bool goingUp = false, goingDown = false;

    //Current position
    int sPosX = SCREEN_WIDTH - 220*1.5, sPosY = SCREEN_HEIGHT - 350*1.5;

    //Velocity
    int sVelX, sVelY;

    int frame = 0, velFrame = 1;
    int immortal = 3;
    int var;
    int fruitSize, woodSize;
    
    Texture snake;
    SDL_Rect snakeClips[5];
    
    Timer time;
    Timer timer;

    std::vector<Fruit*> fruit;
    Wood* wood;
    Collision snakeCol[5];
};