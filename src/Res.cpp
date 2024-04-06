#include "Res.h"

TTF_Font *menuFont,											 // Menu font
	*titleFont, *versionFont, *scoreFont, *highestScoreFont; // Title font


Texture title, version; // Title texture
Texture background, helpground, musicOn, soundOn, musicOff, soundOff, gameground, stand, loseground, heart, groundFruit; // Background texture
Texture snake, snakeCute[51];

Mix_Music *music;
Mix_Chunk *clickSound, *leaveSound, *levelSound, *loseSound, *receiveSound, *wasteSound, *warningSound; // Sound

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

void loadImage(SDL_Renderer *renderer, Texture &texture, const char *path)
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
