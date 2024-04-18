#include "wood.h"
#include "Game.h"

Wood::Wood()
{
    random();
    posX = -SIZEW;
    for (int i = 0; i < 5; i++)
        clips[i] = {i * SIZEW, 0, SIZEW, SIZEW};
}

Wood::~Wood()
{
}

void Wood::random()
{
    int type = rand() % 2;
    switch (type)
    {
    case 0:
        loadImage(wood, "assets/background/1x/1x/typeWood1.png");
        break;

    case 1:
        loadImage(wood, "assets/background/1x/1x/typeWood2.png");
        break;
    }

    timer.start();
    frame = 0;
    posX = 0;
    posY = 610;
    woodCol.setCollision(posX, posY, SIZEW, SIZEW);
    velX = randVel;
}

bool Wood::checkCollision(const Collision &x)
{
    return woodCol.checkCollision(x);
}

void Wood::move()
{
    posX += velX;

    if (posX > SCREEN_WIDTH)
    {
        random();
        posX = -SIZEW;
        // velX = 1.5; // rand() % maxVel + 1.5;
    }
}

void Wood::render()
{
    if (timer.get_ticks() % 3 == 0)
        frame++;
    if (frame == 5)
        frame = 0;
    SDL_Rect *currentClip = &clips[frame];

    woodCol.setCollision(posX, posY, SIZEW, SIZEW);
    wood.render(posX, posY, SIZEW, SIZEW, currentClip, NULL);
    //woodCol.render();
}

void Wood::generate(bool isPaused)
{
    if (isPaused)
        timer.pause();
    else
    {
        timer.unpause();
        move();
    }
    render();
}

double Wood::getPosX()
{
    return posX;
}

double Wood::getPosY()
{
    return posY;
}

Collision Wood::getCol()
{
    return woodCol;
}