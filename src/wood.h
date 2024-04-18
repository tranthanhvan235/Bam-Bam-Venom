#pragma once

#include "const.h"
#include "Timer.h"
#include "Res.h"
#include "Collision.h"

class Wood
{
public:
    Wood();
    ~Wood();

    void random();
    void render();
    void move();
    void generate(bool isPaused);
    double getPosX();
    double getPosY();
    bool checkCollision(const Collision &x);
    Collision getCol();
    int SIZEW = 113;
    double posX, posY;

private:
    double velX, velY;
    int frame;
    Texture wood;
    Timer timer;
    Collision woodCol;
    SDL_Rect clips[5];
};