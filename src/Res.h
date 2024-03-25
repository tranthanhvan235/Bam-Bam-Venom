#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "const.h"
#include "Texture.h"

bool init(SDL_Window *&window, SDL_Renderer *&renderer);

void load(SDL_Renderer *&renderer);

void quit(SDL_Window *&window, SDL_Renderer *&renderer);
