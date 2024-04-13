#pragma once

#include "Fruit.h"

class Snake
{
public:
    // Constructor and destructor
    Snake();
    ~Snake();

    int SNAKEWIDTH = 250 * 1.5, SNAKEHEIGHT = 250*1.5;

    void handleEventSnake(SDL_Event &e);
    void updateGame();

    bool checkCollision(int i);
    
    void render(int i);

    bool isRender = 0;
    //Current position
    int sPosX = SCREEN_WIDTH - 220*1.5, sPosY = SCREEN_HEIGHT - 350*1.5;

    //Velocity
    int sVelX, sVelY;

    int mouseX,mouseY;

    int frame = 0;
    int preMouseX, preMouseY;
    
    Texture snake;
    SDL_Rect snakeClips[8];

    Timer time;
    Timer timer;

    Fruit fruit;
};