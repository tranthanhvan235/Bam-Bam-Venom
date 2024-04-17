#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            // SDL_GetKeyName(Game::event.key.keysym.sym); // tra ve ten cua phim
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
            case SDLK_UP:
                transform->velocity.y = -1;
                break;

            case SDLK_a:
            case SDLK_LEFT:
                transform->velocity.x = -1;
                break;

            case SDLK_s:
            case SDLK_DOWN:
                transform->velocity.y = 1;
                break;

            case SDLK_d:
            case SDLK_RIGHT:
                transform->velocity.x = 1;
                break;

            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                break;
            default:
                break;
            }
        }
    }
};