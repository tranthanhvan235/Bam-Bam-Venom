#include "Fruit.h"
#include "Game.h"

// Constructor and destructor
Fruit::Fruit()
{
    random();
    velY = 4;
    timer.start();
}

Fruit::~Fruit()
{
}
void Fruit::random()
{
    int i = rand() % 9 + 1;
    
    switch (i)
    {
    case GRAPE:
        loadImage(fruit, "assets/fruit/grape.png");
        break;

    case PINEAPPLE:
        loadImage(fruit, "assets/fruit/pineapple.png");
        break;

    case CHERRY:
        loadImage(fruit, "assets/fruit/cherry.png");
        break;

    case LEMON:
        loadImage(fruit, "assets/fruit/lemon.png");
        break;

    case WATERMELON:
        loadImage(fruit, "assets/fruit/watermelon.png");
        break;

    case KIWI:
        loadImage(fruit, "assets/fruit/kiwi.png");
        break;

    case STRAWBERRY:
        loadImage(fruit, "assets/fruit/strawberry.png");
        break;

    case PEAR:
        loadImage(fruit, "assets/fruit/pear.png");
        break;

    case ORANGE:
        loadImage(fruit, "assets/fruit/orange.png");
        break;

    default:
        break;
    }
    eaten = 0;
    posY = 0;
    posX = -fruit.getWidth();
    fruitCol.setCollision(posX, posY, fruit.getWidth() - 50, fruit.getHeight() - 50);
    frame = 0;
    velX = 1.5;
}

bool Fruit::checkCollision(const Collision &x)
{
    if(fruitCol.checkCollision(x))
    {
        eaten = true;
        score += 10;
		Mix_PlayChannel(-1, eatSound, 0);
        random();
        return 1;
    }
    return 0;
}

void Fruit::moveFruit()
{
    if (posY < 500)
        posY += velY;
    posX += velX;

    if (posX > SCREEN_WIDTH)
    {
        posX = -fruit.getWidth();
    }
}
// Render
void Fruit::render()
{
    fruitCol.setCollision(posX + 40, posY + 40, fruit.getWidth() - 80, fruit.getHeight() - 80);
    fruit.render(posX, posY, fruit.getHeight(), fruit.getHeight(), NULL);
}

void Fruit::generate()
{
    moveFruit();
    render();
}

double Fruit::getPosX()
{
    return posX;
}

double Fruit::getPosY()
{
    return posY;
}

double Fruit::getWidth()
{
    return fruit.getWidth();
}

double Fruit::getHeight()
{
    return fruit.getHeight();
}

Collision Fruit::getCol()
{
    return fruitCol;
}