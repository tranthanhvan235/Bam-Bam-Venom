#include "Snake.h"

Snake::Snake()
{
    updateGame();
}

Snake::~Snake()
{

}

void Snake::handleEventSnake(SDL_Event& e)
{
    SDL_GetMouseState(&mouseX, &mouseY);

    time.start();
}

void Snake::updateGame()
{
    for (int i = 0; i < 5; i++)
		snakeClips[i] = {i * 1600, 0, 1600, 1600};
    loadImage(snake, "assets/character/1x/snake_done.png");
    timer.start();
}

bool Snake::checkCollision(int i)
{
    std::cout << sPosX << " " << sPosY << '\n';
    std::cout << fruit.getPosX(i) << " " << fruit.getPosY(i) << "\n";
    std::cout << '\n';
    if (sPosX + SNAKEWIDTH/2 >= fruit.getPosX(i)
            && fruit.getPosX(i) + fruit.getWidth(i)>= sPosX + SNAKEWIDTH/2
            && sPosY + SNAKEHEIGHT >=  fruit.getPosY(i)
            && fruit.getPosY(i) + fruit.getHeight(i) >= sPosY)
    {
        std::cout << "Var\n";
        return true;
    }
    return false;
}

void Snake::render(int i)
{
    if(!isRender) frame = 0;
    fruit.generate(i);
    if(frame == 5) frame = 0;
    SDL_Rect *currentClip = &snakeClips[4];
    //std::cout << "Frame" << " " << frame << "\n";
    //snake.render(SCREEN_WIDTH - 220*1.5, SCREEN_HEIGHT - 350*1.5, 250*1.5, 250*1.5, currentClip, NULL);
	snake.render(sPosX, sPosY, SNAKEWIDTH, SNAKEHEIGHT, currentClip, NULL);
    
    if(timer.get_ticks()%3 == 0) frame++;
    //std::cout << "Do you call me?/n";
}