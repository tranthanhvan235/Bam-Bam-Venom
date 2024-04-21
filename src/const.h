#pragma once

#include <SDL.h>

extern int score;
extern int level;
extern int live;
extern int highestScore;
extern double randVel;
extern int velFrame;

// WINDOWS VARIABLES
// Screen size
const int  SCREEN_WIDTH = 1366;
const int  SCREEN_HEIGHT = 768;

const char WINDOW_TITLE[] = "Bam Bam Venom";
const char VERSION_INFO[] = "VERSION: 1.0";
const char PAUSED_GAME[] = "Pause";
const char LEVEL_UP[] = "LEVEL UP !";
const char EXTERNAL_TIME[] = "EXTERNAL TIME !";

//Frame rate
const int FPS = 60;
const int DELAY_TIME = 1000/FPS;

// MENU VARIABLES
// Game state

enum gameState
{
    QUIT = 0,
    MENU = 1,
    PLAY = 2,
    HELP = 3,
    LOSE = 4,
	MODE = 5
};

// Buttons
const int NUM_BUTTONS = 3;
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 75;

// Fonts
const int MENU_SIZE = 70;

const int TITLE_WIDTH = 500;
const int TITLE_HEIGHT = 100;
const int TITLE_SIZE = 100;

const int VERSION_POSX = SCREEN_WIDTH - 10;
const int VERSION_POSY = 10;
const int VERSION_SIZE = 25;
const int VERSION_WIDTH = 100;
const int VERSION_HEIGHT = 50;
const int LEVEL_SIZE = 80;

// Icons
const int SOUND_POSX = 100;
const int SOUND_POSY = 5;

const int MUSIC_POSX = 40;
const int MUSIC_POSY = 10;

const int SOUND_WIDTH = 60;
const int SOUND_HEIGHT = 60;

const int MUSIC_WIDTH = 50;
const int MUSIC_HEIGHT = 50;

// Button state: Music, Sound
enum binaryState
{
	ON = 1,
	OFF = 0
};

// GAME VARIABLES
// Score
const int SCORE_POSX = 10;
const int SCORE_POSY = 10;
const int SCORE_SIZE = 40;

// Highest score
const int HIGHEST_SCORE_POSX = SCREEN_WIDTH / 2 - 350;
const int HIGHEST_SCORE_POSY = SCREEN_HEIGHT / 2 + 150;
const int HIGHEST_SCORE_SIZE = 50;

// Live
const int START_LIVE = 3;
const int MAX_LIVE = 5;
const int MIN_LIVE = 1;

const int LIVE_POSX = SCREEN_WIDTH - 225;
const int LIVE_POSY = 10;
const int LIVE_DISTANCE = 40;
const int LIVE_WIDTH = 30;
const int LIVE_HEIGHT = 30;

// Immortal
const int IMMORTAL_POSX = SCREEN_WIDTH/2;
const int IMMORTAL_POSY = 10;

// Level
const int MIN_LEVEL = 1;
const int MAX_LEVEL = 6;
// const int LEVEL_POINT[] = {0, 50, 100, 250, 350, 700};

const int LEVEL_POINT[] = {0, 10, 20, 30, 40, 50, 100};
// FRUIT VARIABLES
const int NUM_FRUIT = 11;

// Fruit type
enum fruitType
{
	NOTHING = 0,
	GRAPE = 1,
	PINEAPPLE = 2,
	CHERRY = 3,
	LEMON = 4,
	WATERMELON = 5,
	KIWI = 6,
	STRAWBERRY = 7,
	PEAR = 8,
	ORANGE = 9, 
	BOMB = 10,
	IMMORTAL = 11
};

const int maxVel = 2;

// COLORS
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color YELLOW = {255, 255, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color PINK = {255, 192, 203, 255};
const SDL_Color BROWN = {132, 78, 51, 255};
const SDL_Color SAND = {216, 164, 100, 255};
const SDL_Color TRANSPARENT = {0, 0, 0, 0};