#include "Snake.h"
#include "Game.h"
#include <math.h>

Snake::Snake()
{
  for (int i = 0; i < 5; i++)
  {
    snakeClips[i] = {i * 1600, 0, 1600, 1600};
    snakeCol[i].setCollision(sPosX + SNAKEWIDTH / 3, sPosY + i * (i - 1) * (i - 2) * 20 + SNAKEHEIGHT / 2, 50, 50);
  }
  
  frame = 0;

  snakeCol[0].setCollision(sPosX + SNAKEWIDTH / 3, sPosY + SNAKEHEIGHT / 2, 50, 50);
  snakeCol[1].setCollision(sPosX + SNAKEWIDTH / 3, sPosY + SNAKEHEIGHT / 2 + 20, 50, 50);
  snakeCol[2].setCollision(sPosX + SNAKEWIDTH / 3, sPosY + SNAKEHEIGHT / 2 + 50, 50, 50);
  snakeCol[3].setCollision(sPosX + SNAKEWIDTH / 3, sPosY + SNAKEHEIGHT / 2 + 80, 50, 50);
  snakeCol[4].setCollision(sPosX + SNAKEWIDTH / 3, sPosY + SNAKEHEIGHT / 2 + 130, 50, 50);
  
  loadImage(snake, "assets/character/1x/snake_done.png");
  timer.start();
}

Snake::~Snake()
{
}
void Snake::reset()
{
}
void Snake::handleEventSnake(SDL_Event &e)
{
}

void Snake::updateGame()
{
  if (frame == 4 && goingDown)
  {
    goingDown = false;
    goingUp = true;
  }
  else if (frame == 0 && goingUp)
  {
    goingUp = false;
    goingDown = false;
  }

  if (goingUp)
    velFrame = -1;
  else if (goingDown)
    velFrame = 1;
  else
    velFrame = 0;
}

void Snake::render(bool isPaused)
{
  updateGame();

  if (isPaused)
    timer.pause();
  else
    timer.unpause();

  if (timer.get_ticks() % 2 == 0)
    frame += velFrame;

  SDL_Rect *currentClip = &snakeClips[frame];
  snake.render(sPosX, sPosY, SNAKEWIDTH, SNAKEHEIGHT, currentClip, NULL);
  //snakeCol[frame].render();
}

Collision Snake::getCol()
{
  //std::cout << frame << '\n';
  // if(frame == 5) std::cout << "bug here\n";
  return snakeCol[frame];
}