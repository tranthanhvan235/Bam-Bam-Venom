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
    
    void render(int i);
    void curRender(bool isPaused);
    void move(int i);
    void generate(bool isPaused);
    double getPosX(int i);
    double getPosY(int i);
    double getWidth(int i);
    double getHeight(int i);
    bool checkCollision(const Collision &x);
    Collision getCol(int i);
    int curId = 0, nextId = 1;

private:
    double posX[2], posY[2];
    double velX[2], velY[2];
    int frame;
    Texture wood[2][2];
    Timer timer;
    Collision woodCol[2];
};