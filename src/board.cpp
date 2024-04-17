#include "board.h"
#include "Game.h"

Board::Board()
{
    for (int i = 0; i < 2; i++)
    {
        loadImage(board[i], "assets/background/groundFruit.png");
        posX[i] = -board[i].getWidth() * 3;
        posY[i] = 610;
        boardCol[i].setCollision(posX[i], posY[i], board[i].getWidth(), board[i].getHeight());
        timer[i].start();
        velX[i] = 1.5;
    
    }
    // frame = 0;
    // posX = -board.getWidth() - 50;
    // rand() % maxVel + 1.5;
}

Board::~Board()
{
}

void Board::move(int i)
{
    posX[i] += velX[i];

    if (posX[i] > SCREEN_WIDTH)
    {
        posX[i] = -board[i].getWidth() * 3;
        std::swap(nextId, curId);
        //velX[i] = 1.5; // rand() % maxVel + 1.5;
    }
}

void Board::render(int i)
{
    boardCol[i].setCollision(posX[i], posY[i], board[i].getWidth()*3, board[i].getHeight());
    board[i].render(posX[i], posY[i], board[i].getWidth() * 3, board[i].getHeight(), NULL);
    //boardCol[i].render();
}

void Board::curRender()
{
    if(posX[curId] + board[curId].getWidth() * 3 > SCREEN_WIDTH)
       {
         move(nextId); 
         render(nextId);
       }
    render(curId);
}

void Board::generate()
{
    move(curId);
    curRender();
}

double Board::getPosX()
{
    return posX[1];
}

double Board::getPosY()
{
    return posY[1];
}

double Board::getWidth()
{
    return board[1].getWidth();
}

double Board::getHeight()
{
    return board[1].getHeight();
}
