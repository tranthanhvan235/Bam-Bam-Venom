#pragma once

#include "const.h"
#include "Timer.h"
#include "Res.h"
#include "Collision.h"

class Board
{
public:
    Board();
    ~Board();
    // Render
    void render(int i);
    void curRender();

    void move(int i);
    void generate();

    double getPosX();
    double getPosY();
    double getWidth();
    double getHeight();

    double posX[2], posY[2];
    double velX[2], velY[2];
    Collision boardCol[2];
    int curId = 0, nextId = 1;

private:
    Timer timer[2];
    Texture board[2];
};