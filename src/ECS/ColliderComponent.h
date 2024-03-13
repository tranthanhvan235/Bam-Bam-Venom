#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"

class ColliderComponent : public Component
{
    SDL_Rect collider
};