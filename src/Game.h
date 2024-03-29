#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "const.h"
#include "Res.h"

class Game
{
public:
    Game();
    ~Game();

    bool init();
    void load();

    void play();
    void menu();
    void help();
    void lose();
    
    void quit();

    void gameReset();
    void menuReset();

    void handlePlayEvent();

    void setGameState(const int &state);
    void manageState();

    static SDL_Event event;
    static SDL_Renderer *renderer;
private:
    int gameState;
    
    bool musicState = ON;
    bool soundState = ON;

    bool loop = true;
    SDL_Window *window;
};
