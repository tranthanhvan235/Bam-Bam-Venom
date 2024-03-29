#include "Map.h"

int lvl1[20][25];
Map::Map()
{
    //dirt = TextureManager::LoadTexture("assets/dirt.png");
    //grass = TextureManager::LoadTexture("assets/grass.png");
    //water = TextureManager::LoadTexture("assets/water.png");

    LoadMap(lvl1);

    src.x = src.y = 0;

    src.w = dest.w = 1;
    src.h = dest.h = 1;

    dest.x = dest.y = 0;
}

Map::~Map()
{
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(water);
    SDL_DestroyTexture(dirt);
}
void Map::LoadMap(int arr[20][25])
{
    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 25; col++)
        {
            map[row][col] = arr[row][col];
        }
    }
}
void Map::DrawMap()
{
    int type = 0;
    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 25; col++)
        {
            type = map[row][col];

            dest.y = row * 32;
            dest.x = col * 32;

            /*switch (type)
            {
            case 0:
                TextureManager::Draw(water, src, dest);
                break;
            case 1:
                TextureManager::Draw(grass, src, dest);
                break;
            case 2:
                TextureManager::Draw(dirt, src, dest);
                break;
            default:
                break;
            }*/
        }
    }
}