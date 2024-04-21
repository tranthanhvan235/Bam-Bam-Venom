#include "Res.h"

TTF_Font *menuFont,											 // Menu font
	*titleFont, *versionFont, *scoreFont, *highestScoreFont, *levelUpFont, *pausedFont; // Title font


Texture title, version, paused, LevelUP; // Title texture
Texture background, backgroundFull, helpground, musicOn, soundOn, musicOff, soundOff, gameground, stand, loseground, heart, immortalOn, immortalOff; // Background texture
Texture snakeCute[51];

Mix_Music *music, *helpMusic;
Mix_Chunk *music_soundClick, *clickSound, *externalTime, *levelSound, *loseSound, *eatSound, *endImmortalTime, *jumpSound, *fruitDown, *varSound, *transSound; // Sound

const char *menuText[NUM_BUTTONS] = {"Play", "Help", "Quit"}; // Menu text

std::vector<Button> buttons;
SDL_Rect musicRect = {MUSIC_POSX, MUSIC_POSY, MUSIC_WIDTH, MUSIC_HEIGHT};
SDL_Rect soundRect = {SOUND_POSX, SOUND_POSY, SOUND_WIDTH, SOUND_HEIGHT};
Button musicButton(musicRect, TRANSPARENT, menuFont, TRANSPARENT);
Button soundButton(soundRect, TRANSPARENT, menuFont, TRANSPARENT);

void loadFont(TTF_Font *&font, const char *path, const int &size)
{
	font = TTF_OpenFont(path, size);
	if (font == nullptr)
	{
		std::cout << "Failed to load font! Error: " << TTF_GetError() << std::endl;
	}
}

void loadImage(Texture &texture, const char *path)
{
	if (!texture.loadFromFile(path))
	{
		std::cout << "Failed to load image! Error: " << SDL_GetError() << std::endl;
	}
}

void loadMusic(Mix_Music *&music, const char *path)
{
	music = Mix_LoadMUS(path);
	if (music == nullptr)
	{
		std::cout << "Failed to load music! Error: " << Mix_GetError() << std::endl;
	}
}

void loadSound(Mix_Chunk *&sound, const char *path)
{
	sound = Mix_LoadWAV(path);
	if (sound == nullptr)
	{
		std::cout << "Failed to load sound! Error: " << Mix_GetError() << std::endl;
	}
}
