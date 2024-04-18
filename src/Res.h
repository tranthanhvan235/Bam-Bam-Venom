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
	*titleFont, *versionFont, *scoreFont, *highestScoreFont, *levelUpFont, *pausedFont; // Title font

extern Texture title, version, paused, LevelUP; // Title texture
extern Texture background, backgroundFull, helpground, musicOn, soundOn, musicOff, soundOff, gameground, stand, loseground, heart; // Background texture
extern Texture snakeCute[51];

extern Mix_Music *music;
extern Mix_Chunk *music_soundClick, *clickSound, *leaveSound, *levelSound, *loseSound, *eatSound, *wasteSound, *warningSound, *jumpSound, *fruitDown, *varSound, *transSound; // Sound

extern const char *menuText[NUM_BUTTONS];// Menu text

extern std::vector<Button> buttons;
extern SDL_Rect musicRect;
extern SDL_Rect soundRect;
extern Button musicButton;
extern Button soundButton;

void loadFont(TTF_Font *&font, const char *path, const int &size);
void loadImage(Texture &texture, const char *path);
void loadMusic(Mix_Music *&music, const char *path);
void loadSound(Mix_Chunk *&sound, const char *path);
//bool checkCollisionSnake_Fruit(Snake &snake, Fruit &fruit);