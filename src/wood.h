#pragma once

#include "const.h"
#include "Timer.h"
#include "Res.h"
#include "Collision.h"

const int WOODSIZE = 13;

class Wood
{
public:
    Wood();
    ~Wood();

    void random(int i);
    void render();
    void move();
    void generate();
    double getPosX(int i);
    double getPosY(int i);
    bool checkCollision(const Collision &x);
    Collision getCol(int i);
    int SIZEW = 113;

private:
    double posX[WOODSIZE], posY[WOODSIZE];
    double velX[WOODSIZE], velY[WOODSIZE];
    int frame;
    Texture wood[WOODSIZE];
    Timer timer;
    Collision woodCol[WOODSIZE];
    SDL_Rect clips[5];
};