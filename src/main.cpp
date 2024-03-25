#include "Game.h"
#include "Res.h"

SDL_Window *window;
SDL_Renderer *renderer;
Game game;

int score;
int level;
int live;
int highestScore;

int main(int argc, char *args[])
{
    srand(time(NULL));
    
    if(init(window, renderer))
        load(renderer);
    
    game.setGameState(MENU);
    game.manageState(renderer);

    quit(window, renderer);
    return 0;
}
