#include "Fruit.h"

// Constructor and destructor
Fruit::Fruit()
{
    update();
}

Fruit::~Fruit()
{
}
void Fruit::update()
{
    for (int i = 0; i < NUM_FRUIT; i++)
    {
        switch (i)
        {
        case GRAPE:
            loadImage(fruit[i], "assets/fruit/grape.png");
            break;

        case PINEAPPLE:
            loadImage(fruit[i], "assets/fruit/pineapple.png");
            break;

        case CHERRY:
            loadImage(fruit[i], "assets/fruit/cherry.png");
            break;

        case LEMON:
            loadImage(fruit[i], "assets/fruit/lemon.png");
		    break;

        case WATERMELON:
            loadImage(fruit[i], "assets/fruit/watermelon.png");
            break;

        case KIWI:
            loadImage(fruit[i], "assets/fruit/kiwi.png");
            break;

        case STRAWBERRY:
            loadImage(fruit[i], "assets/fruit/strawberry.png");
            break;

        case PEAR:
            loadImage(fruit[i], "assets/fruit/pear.png");
            break;
        case ORANGE:
            loadImage(fruit[i], "assets/fruit/orange.png");
            break;

        default:
            break;
        }
    }
    for (int i = 0; i < NUM_FRUIT; i++)
    {
        frame[i] = 0;
        timer[i].start();
        posX[i] = -fruit[i].getWidth() - 50;
        posY[i] = rand()%(SCREEN_HEIGHT - fruit[i].getHeight() - 90 + 1) + 90;
        velX[i] = rand()%maxVel + 1.5;
        velY[i] = rand()%maxVel + 1.5;
    }
}
void Fruit::moveFruit(int i)
{
    posX[i] += velX[i];

    if(posX[i] + fruit[i].getWidth() > SCREEN_WIDTH)
    {
        posX[i] = -fruit[i].getWidth();
        posY[i] = rand()% (SCREEN_HEIGHT - fruit[i].getHeight() - 20);
        velX[i] = rand()%maxVel + 1.5;
    }

    posY[i] += velY[i] * 0.35;

    if(posY[i] <= 86)
    {
        velY[i] = -velY[i];
        posY[i] += velY[i];
    }

    if(posY[i] + fruit[i].getHeight() > SCREEN_HEIGHT - 10)
    {
        velY[i] = -velY[i];
        posY[i] += velY[i];
    }
}
// Render
void Fruit::render(int i)
{
    if(frame[i] == 3) frame[i] = 0;
    int index = 3 * i + frame[i];
    fruit[i].render(posX[i], 500, 166, 166, NULL);
    if(timer[i].get_ticks() % 15 == 0) frame[i]++;
}

void Fruit::generate(int i)
{
    moveFruit(i);
    render(i);
}

double Fruit::getPosX(int i)
{
    return posX[i];
}

double Fruit::getPosY(int i)
{
    return posY[i];
}

double Fruit::getWidth(int i)
{
    return fruit[i].getWidth();
}

double Fruit::getHeight(int i)
{
    return fruit[i].getHeight();
}