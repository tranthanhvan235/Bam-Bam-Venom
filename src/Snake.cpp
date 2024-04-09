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

}

void Snake::checkCollision()
{

}

void Snake::render()
{
    fruit[1].generate(1);
    if(frame == 5) frame = 0;
    SDL_Rect *currentClip = &snakeClips[frame];
    std::cout << "Frame" << " " << frame << "\n";
	snake.render(SCREEN_WIDTH - 220*1.5, SCREEN_HEIGHT - 350*1.5, 250*1.5, 250*1.5, currentClip, NULL);
	//snake.render(sPosX, sPosY, SNAKEWIDTH, SNAKEHEIGHT, currentClip, NULL);
    
    if(timer.get_ticks()%50 == 0) frame++;
    //std::cout << "Do you call me?/n";
}