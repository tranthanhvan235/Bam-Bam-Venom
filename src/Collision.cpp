#include "Collision.h"
#include "Game.h"

Collision::Collision()
{
}
Collision::~Collision()
{
}
void Collision::setCollision(double xx, double yy, double ww, double hh)
{
    x = xx;
    y = yy;
    w = ww;
    h = hh;
}
void Collision::render()
{
    SDL_Rect rec;
    rec = {(int)x, (int) y, (int)w, (int) h};
    SDL_RenderFillRect(Game::renderer, &rec);
}
bool Collision::checkCollision(const Collision &recB)
{
    return (
        x + w >= recB.x &&
        recB.x + recB.w >= x &&
        y + h >= recB.y &&
        recB.y + recB.h >= y);
}
