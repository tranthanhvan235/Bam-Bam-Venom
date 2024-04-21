#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Texture.h"
#include "const.h"
#include "Res.h"
#include "ultils.h"
#include "Fruit.h"
#include "wood.h"
#include "Snake.h"

class ColliderComponent;
class Game
{
public:
    Game();
    ~Game();

    bool init();
    void load();

    void play();
    void chooseMode();
    void menu();
    void help();
    void lose();
    void renderUpLevel();

    void quit();

    void gameReset();
    void menuReset();

    void handlePlayEvent();

    void setGameState(const int &state);
    void manageState();

    static SDL_Event event;
    static SDL_Renderer *renderer;
    //static std::vector<ColliderComponent*> colliders;

private:
    int gameState;
    int isLevelUp;
    bool musicState = ON;
    bool soundState = ON;
    bool isPaused = false;
    bool isImmortal = false;
	int curId = 0;
    bool loop = true;
    SDL_Window *window;

    std::deque<Fruit*> fruit;
    Wood* wood;
    Snake* snake;

    bool addFruit = false;
    int idStory = 0;
    int playMode;
    int checkCollision(bool immortal);
};
