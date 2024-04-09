#pragma once

#include "Fruit.h"

class Snake
{
public:
    // Constructor and destructor
    Snake();
    ~Snake();

    int SNAKEWIDTH = 250, SNAKEHEIGHT = 250;

    void handleEventSnake(SDL_Event &e);
    void updateGame();

    void checkCollision();
    
    void render();

    //Current position
    int sPosX, sPosY;

    //Velocity
    int sVelX, sVelY;

    int mouseX,mouseY;

    int frame = 0;
    int preMouseX, preMouseY;
    
    Texture snake;
    SDL_Rect snakeClips[8];

    Timer time;
    Timer timer;

    Fruit fruit[NUM_FRUIT];
};