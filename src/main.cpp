#include "Res.h"
#include "Game.h"

Game game;

int score;
int level;
int live;
int highestScore;

int main(int argc, char *args[])
{
    srand(time(NULL));
    
    if(game.init())
        game.load();
    
    game.setGameState(MENU);
    game.manageState();

    game.quit();
    return 0;
}
