#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "const.h"

class Game
{
public:
    Game();
    ~Game();

    void play(SDL_Renderer *renderer);
    void menu(SDL_Renderer *renderer);
    void help(SDL_Renderer *renderer);
    void lose(SDL_Renderer *renderer);

    void gameReset();
    void menuReset();

    void handlePlayEvent(SDL_Renderer *renderer, SDL_Event &event);

    void setGameState(const int &state);
    void manageState(SDL_Renderer *renderer);

private:
    int gameState;

    bool musicState = ON;
    bool soundState = ON;

    bool loop = true;
};
