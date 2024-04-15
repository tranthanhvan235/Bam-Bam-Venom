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
    void render();

    void moveFruit();

    void generate();

    double getPosX();
    double getPosY();
    double getWidth();
    double getHeight();

    double posX, posY;
    double velX, velY;
    Collision fruitCol;

private:
    double frame;
    Timer timer;
    Texture fruit;
};