#include "wood.h"
#include "Game.h"

Wood::Wood()
{
   
    for(int i = 0; i < WOODSIZE; i++)
    {
        random(i);
        posX[i] = -i * SIZEW;
    }
    for (int i = 0; i < 5; i++)
        clips[i] = {i * SIZEW, 0, SIZEW, SIZEW};
    
}

Wood::~Wood()
{
}

void Wood::random(int i)
{
    int type = rand() % 2;
    switch (type)
    {
    case 0:
        loadImage(wood[i], "assets/background/1x/1x/typeWood1.png");
        break;

    case 1:
        loadImage(wood[i], "assets/background/1x/1x/typeWood2.png");
        break;
    }

    timer.start();
    frame = 0;
    posX[i] = 0;
    posY[i] = 610;
    woodCol[i].setCollision(posX[i], posY[i], SIZEW, SIZEW);
    velX[i] = 1.5;
}

bool Wood::checkCollision(const Collision &x)
{
    for (int i = 0; i < WOODSIZE; i++)
        if (woodCol[i].checkCollision(x))
            return true;

    return false;
}

void Wood::move()
{
    for (int i = 0; i < WOODSIZE; i++)
    {
        posX[i] += velX[i];

        if (posX[i] > SCREEN_WIDTH)
        {
            random(i);
            posX[i] = -SIZEW;
            // velX = 1.5; // rand() % maxVel + 1.5;
        }
    }
}

void Wood::render()
{
    if (timer.get_ticks() % 7 == 0)
        frame++;
    if (frame == 5)
        frame = 0;
    SDL_Rect *currentClip = &clips[frame];
    for(int i = 0; i < WOODSIZE; i++)
    {
    woodCol[i].setCollision(posX[i], posY[i], SIZEW, SIZEW);
    wood[i].render(posX[i], posY[i], SIZEW, SIZEW, currentClip, NULL);
    //woodCol[i].render();
    }
}

void Wood::generate()
{
    move();
    render();
}

double Wood::getPosX(int i)
{
    return posX[i];
}

double Wood::getPosY(int i)
{
    return posY[i];
}

Collision Wood::getCol(int i)
{
    return woodCol[i];
}