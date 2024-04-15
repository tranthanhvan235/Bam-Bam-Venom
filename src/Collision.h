#pragma once
#include <SDL.h>

class Collision
{
public:
    Collision();
    ~Collision();
    double x, y, w, h;
    void setCollision(double x, double y, double w, double h);
    bool checkCollision(const Collision& recB);
    void render();
};