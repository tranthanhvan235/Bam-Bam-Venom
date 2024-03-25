#pragma once

#include "Components.h"
#include "SDL.h"
#include "../Texture.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcREct, destRect;

public:

    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTex(path);    
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char* path) 
    {
       // texture = Texture::LoadTexture(path);
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
        destRect.x = static_cast<int> (transform->position.x);
        destRect.y = static_cast<int> (transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void draw() override
    {
       // TextureManager::Draw(texture, srcREct, destRect);
    }
};