#include "Fruit.h"

// Constructor and destructor
Fruit::Fruit()
{
    random();
    timer.start();
    velY = randVel + 2;
    posY = 0;
}

Fruit::~Fruit()
{
}
void Fruit::random()
{
    int i = rand() % NUM_FRUIT + 1 ;
    type = i;
    //std::cout << type << '\n';
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

    case BOMB:
        loadImage(fruit, "assets/fruit/bomb.png");
        break;

    case IMMORTAL:
        loadImage(fruit, "assets/fruit/immortal.png");
        break;

    default:
        break;
    }
    eaten = 0;
    fruitCol.setCollision(posX, posY, fruit.getWidth() - 50, fruit.getHeight() - 50);
    frame = 0;
    velX = 0.5;
    posY = -(rand() % 50) - 50;
}

void handleEvent(SDL_Event &e)
{
    
}

bool Fruit::checkCollision(const Collision &x)
{
    if(fruitCol.checkCollision(x))
    {
        eaten = true;
        return 1;
    }
    return 0;
}

void Fruit::moveFruit()
{
    int onGround = 500;
    if (posY < onGround)
        {
            posY += velY;
            if(posY >= onGround && posX >= 0)
            {
                Mix_PlayChannel(-1, fruitDown, 0);
            }
   
        }
    else velX = randVel;
    
    posX += velX;
}
// Render
void Fruit::render()
{
    fruitCol.setCollision(posX + 40, posY + 40, fruit.getWidth() - 80, fruit.getHeight() - 80);
    fruit.render(posX, posY, fruit.getHeight(), fruit.getHeight(), NULL);
    //fruitCol.render();
}

void Fruit::generate(bool isPaused)
{
    if(!isPaused)
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

int Fruit::getType()
{
    return type;
}

double Fruit::calcPosX()
{
    double t = (500 - posY)/velY;
    double futurePosX = posX + t * velX;
    return futurePosX;
}