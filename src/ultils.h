#pragma once

#include <string>
#include <stdlib.h>
#include <fstream>
#include <ostream>

#include "Texture.h"
#include "const.h"
#include "Res.h"


int random(const int &min, const int &max);

void showLive(SDL_Renderer *renderer);

void showScore(SDL_Renderer *renderer);

void readHighestScore();
void updateHighestScore();
void showHighestScore(SDL_Renderer *renderer);

int levelUp();