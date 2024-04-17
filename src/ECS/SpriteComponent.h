#pragma once

#include "../Texture.h"
#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    Texture *texture;
    SDL_Rect srcREct, destRect;

public:
    SpriteComponent() = default;
    SpriteComponent(std::string path)
    {
        texture->loadFromFile(path);
    }

    ~SpriteComponent()
    {
        texture->free();
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcREct.x = srcREct.y = 0;
        srcREct.w = transform->width;
        srcREct.h = transform->height;
    }

    void update() override
    {
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override
    {
        texture->render(destRect.x, destRect.y, srcREct.w, srcREct.h, NULL);
    }
};