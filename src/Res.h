#pragma once

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "button.h"
#include "const.h"
#include "Texture.h"

extern TTF_Font *menuFont,									 // Menu font
	*titleFont, *versionFont, *scoreFont, *highestScoreFont; // Title font

extern Texture title, version; // Title texture
extern Texture background, helpground, musicOn, soundOn, musicOff, soundOff, gameground, stand, loseground, heart; // Background texture

extern Mix_Music *music;
extern Mix_Chunk *clickSound, *leaveSound, *levelSound, *loseSound, *receiveSound, *wasteSound, *warningSound; // Sound

extern const char *menuText[NUM_BUTTONS];// Menu text

extern std::vector<Button> buttons;
extern SDL_Rect musicRect;
extern SDL_Rect soundRect;
extern Button musicButton;
extern Button soundButton;


bool init(SDL_Window *&window, SDL_Renderer *&renderer);

void load(SDL_Renderer *&renderer);

void quit(SDL_Window *&window, SDL_Renderer *&renderer);
