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
  fruitSize = rand() % 10 + 2;
  for (int i = 0; i < fruitSize; i++)
  {
    Fruit *newFruit = new Fruit();
    if (fruit.size())
    {
      newFruit->velY = fruit[fruit.size() - 1]->velY + rand() % 2;
      newFruit->posX = fruit[fruit.size() - 1]->posX - newFruit->getWidth() - rand() % 20;
      newFruit->posY = fruit[fruit.size() - 1]->posY - newFruit->getHeight() * i;
    }
    fruit.push_back(newFruit);
  }
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
  for (int i = 0; i < fruitSize; i++)
    if (fruit[i]->checkCollision(snakeCol[frame]))
    {
      immortal = 10;
      return 1;
    }
  if (wood.checkCollision(snakeCol[frame]))
  {
    immortal--;
    if (immortal)
      return 0;
    Mix_PlayChannel(-1, varSound, 0);
    return 2;
  }
  return 0;
}

void Snake::render(bool isPaused)
{
  wood.generate(isPaused);
  for (int i = 0; i < fruitSize; i++)
    fruit[i]->generate(isPaused);

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
  
  if(isPaused) timer.pause();
  else timer.unpause();
  
  if (timer.get_ticks() % 3 == 0)
    frame += velFrame;
  
  SDL_Rect *currentClip = &snakeClips[frame];
  snake.render(sPosX, sPosY, SNAKEWIDTH, SNAKEHEIGHT, currentClip, NULL);
}
