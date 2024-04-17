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

    void generate();

    double getPosX();
    double getPosY();
    double getWidth();
    double getHeight();
    Collision getCol();
    int eaten = false;

private:
    double frame;
    Timer timer;
    Texture fruit; 
    double posX, posY;
    double velX, velY;
    Collision fruitCol;
};