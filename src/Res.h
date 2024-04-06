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
extern Texture background, helpground, musicOn, soundOn, musicOff, soundOff, gameground, stand, loseground, heart, groundFruit; // Background texture
extern Texture snake, snakeCute[51];

extern Mix_Music *music;
extern Mix_Chunk *clickSound, *leaveSound, *levelSound, *loseSound, *receiveSound, *wasteSound, *warningSound; // Sound

extern const char *menuText[NUM_BUTTONS];// Menu text

extern std::vector<Button> buttons;
extern SDL_Rect musicRect;
extern SDL_Rect soundRect;
extern Button musicButton;
extern Button soundButton;

void loadFont(TTF_Font *&font, const char *path, const int &size);
void loadImage(SDL_Renderer *renderer, Texture &texture, const char *path);
void loadMusic(Mix_Music *&music, const char *path);
void loadSound(Mix_Chunk *&sound, const char *path);
