#include "wood.h"
#include "Game.h"

Wood::Wood()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            switch (j)
            {
            case 0:

                loadImage(wood[i][j], "assets/background/typeWood1.png");
                break;

            case 1:
                loadImage(wood[i][j], "assets/background/typeWood2.png");

                break;
            }
        }
        posY[i] = 610;
        posX[i] = -wood[i][0].getWidth();
        velX[i] = randVel;
        woodCol[i].setCollision(posX[i], posY[i], wood[0][0].getWidth(), wood[0][0].getHeight());
    }
    timer.start();
    frame = 0;
}

Wood::~Wood()
{
}

bool Wood::checkCollision(const Collision &x)
{
    for (int i = 0; i < 2; i++)
        if (woodCol[i].checkCollision(x))
            return true;

    return false;
}

void Wood::move(int i)
{
    posX[i] += velX[i];

    if (posX[i] + wood[i][0].getWidth()> SCREEN_WIDTH)
    {
        std::swap(nextId, curId);
        posX[nextId] = 0;
        //velX[i] = randVel;
        // velX[i] = 1.5; // rand() % maxVel + 1.5;
    }
}

void Wood::render(int i)
{
    woodCol[i].setCollision(posX[i], posY[i], wood[0][0].getWidth(), wood[0][0].getHeight());
    wood[i][frame].render(posX[i], posY[i], wood[0][0].getWidth(), wood[0][0].getHeight(), NULL);
    // woodCol[i].render();
}

void Wood::curRender(bool isPaused)
{
    if (posX[curId] + wood[curId][frame].getWidth() * 3> SCREEN_WIDTH)
    {
        if (!isPaused)
            move(nextId);
        render(nextId);
    }
    render(curId);
}
void Wood::generate(bool isPaused)
{
    if (timer.get_ticks() % 5 == 0)
        frame++;
    if (frame == 2)
        frame = 0;
    
    if (!isPaused)
    {
        move(curId);
       // timer.unpause();
    }
   // else
    //    timer.pause();
    curRender(isPaused);
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