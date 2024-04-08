#pragma once

#include "const.h"
#include "Timer.h"
#include "Res.h"

class Fruit
{
public:
    // Constructor and destructor
    Fruit();
    ~Fruit();

    void update();

    // Render
    void render(int i);

    void moveFruit(int i);

    void generate(int i);

    double getPosX(int i);
    double getPosY(int i);
    double getWidth(int i);
    double getHeight(int i);

    double posX[NUM_FRUIT], posY[NUM_FRUIT];
    double velX[NUM_FRUIT], velY[NUM_FRUIT];

private:
    double frame[NUM_FRUIT];
    Timer timer[NUM_FRUIT];
    Texture fruit[NUM_FRUIT];
};