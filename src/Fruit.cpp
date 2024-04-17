#include "Fruit.h"

// Constructor and destructor
Fruit::Fruit()
{
    random();
    velX = 1.5;
    velY = 3;
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
    timer.start();
}
void Fruit::moveFruit()
{
    if(posY < 500)
        posY += velY;    
    posX += velX;

    if (posX + fruit.getWidth() > SCREEN_WIDTH)
    {
        posX = -fruit.getWidth();
        velX = 1.5; //rand() % maxVel + 1.5;
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