#pragma once

#include "const.h"
#include "Timer.h"
#include "Res.h"
#include "Collision.h"

class Fruit
{
public:
    // Constructor and destructor
    Fruit();
    ~Fruit();

    // Render
    void random();
    void render();

    void moveFruit();

    void generate(bool isPaused);

    double getPosX();
    double getPosY();
    double getWidth();
    double getHeight();
    int getType();
    Collision getCol();
    bool checkCollision(const Collision &x);
    int eaten = false;
    double posX, posY;
    double velX, velY;
    double calcPosX();

private:
    double frame;
    Timer timer;
    Texture fruit; 
    Collision fruitCol;
    int type;
};