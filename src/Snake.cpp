#include "Snake.h"
#include "Game.h"

Snake::Snake()
{
  for (int i = 0; i < 5; i++)
  {
    snakeClips[i] = {i * 1600, 0, 1600, 1600};
    snakeCol[i].setCollision(sPosX + SNAKEWIDTH / 3, sPosY + i * (i - 1) * (i - 2) * 20 + SNAKEHEIGHT / 2, 50, 50);
    // SDL_RenderDrawPoint(Game::renderer, sPosX + SNAKEWIDTH / 2, sPosY + SNAKEHEIGHT);
  }
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

void Snake::handleEventSnake(SDL_Event &e)
{
}

void Snake::updateGame()
{
}

int Snake::checkCollision()
{
  int i = frame;
  if(snakeCol[i].checkCollision(fruit.fruitCol)) return 1;
  if(snakeCol[i].checkCollision(board.boardCol[0]) || snakeCol[i].checkCollision(board.boardCol[1])) return 2;
  return 0;
}

void Snake::render(bool isPaused)
{
  if (!isPaused)
  {
    board.generate();
    fruit.fruitCol.render();
    fruit.generate();

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

    if (timer.get_ticks() % 3 == 0)
      frame += velFrame;
  }
  else
  {
    board.curRender();
    fruit.render();
  }
  SDL_Rect *currentClip = &snakeClips[frame];
  // std::cout << frame << '\n';
  snake.render(sPosX, sPosY, SNAKEWIDTH, SNAKEHEIGHT, currentClip, NULL);
  snakeCol[frame].render();
}
