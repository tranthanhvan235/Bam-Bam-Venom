#pragma once

#include <SDL.h>

extern int score;
extern int level;
extern int live;
extern int highestScore;

// WINDOWS VARIABLES
// Screen size
const char WINDOW_TITLE[] = "Bam Bam Venom";
const char VERSION_INFO[] = "VERSION: 1.0";

const int  SCREEN_WIDTH = 1366;
const int  SCREEN_HEIGHT = 768;

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
    LOSE = 4
};

// Buttons
const int NUM_BUTTONS = 3;
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 75;

// Fonts
const int MENU_SIZE = 45;

const int TITLE_WIDTH = 500;
const int TITLE_HEIGHT = 100;
const int TITLE_SIZE = 250;

const int VERSION_POSX = SCREEN_WIDTH - 10;
const int VERSION_POSY = 10;
const int VERSION_SIZE = 25;
const int VERSION_WIDTH = 100;
const int VERSION_HEIGHT = 50;

// Icons
const int SOUND_POSX = 10;
const int SOUND_POSY = 10;

const int MUSIC_POSX = 50;
const int MUSIC_POSY = 10;

const int SOUND_WIDTH = 30;
const int SOUND_HEIGHT = 30;

const int MUSIC_WIDTH = 30;
const int MUSIC_HEIGHT = 30;

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
const int SCORE_SIZE = 35;

// Highest score
const int HIGHEST_SCORE_POSX = SCREEN_WIDTH / 2 - 200;
const int HIGHEST_SCORE_POSY = SCREEN_HEIGHT / 2;
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

// Level
const int MIN_LEVEL = 1;
const int MAX_LEVEL = 5;
const int LEVEL_POINT[] = {0, 10, 20, 30, 40};

// CUSTOMER VARIABLES
const int NUM_CUSTOMERS = 5;

// Customer position
const int CUSTOMER_STARTX = 1400;
const int CUSTOMER_STARTY = 625;
const int CUSTOMER_WAITX[] = {350, 550, 750, 950, 1150};
const int CUSTOMER_VELOCITY = 5;

// Customer motion
const int CUSTOMER_MOTION_RECTANGLE = 9;

// Customer's requests
const int CUSTOMER_MAXREQUESTS = 10;

const int CUSTOMER_MIN_INGREDIENTS_REQUEST[] = {0, 3, 3, 5, 7, 7};
const int CUSTOMER_MAX_INGREDIENTS_REQUEST[] = {0, 5, 5, 7, 10, 10};

const int CUSTOMER_REQUESTS_POSX[] = {475, 675, 875, 1075, 1275};
const int CUSTOMER_REQUESTS_POSY = 625;

const int CUSTOMER_BUBBLE_POSX[] = {475, 675, 875, 1075, 1275};
const int CUSTOMER_BUBBLE_POSY = 700;
const int CUSTOMER_BUBBLE_WIDTH = 65;
const int CUSTOMER_BUBBLE_DISTANCE = 20;

const int CUSTOMER_REQUESTS_DISTANCE = 10;

// Customer's waiting state
const int CUSTOMER_BAR_WIDTH = 100;
const int CUSTOMER_BAR_HEIGHT = 10;

const float CUSTOMER_MAX_WAITING_TIME = 100;
const float CUSTOMER_WAITING_TIME[] = {0.0, 0.01, 0.02, 0.03, 0.04, 0.05};

// Customer type
enum customerType
{
	GHOST = 0,
	FOX = 1,
	WOLF = 2
};

// Customer status
enum customerStatus
{
	OUTBOUND = 0,
	RUNNING = 1,
	WAITING = 2,
	LEAVING = 3
};

// SELLER VARIABLES
// Seller status
enum sellerStatus
{
	IDLE = 0,
	GO_UP = 1,
	GO_DOWN = 2,
	GO_LEFT = 3,
	GO_RIGHT = 4
};

// Seller position
const int SELLER_STARTX = 475;
const int SELLER_STARTY = 350;
const int SELLER_STEP = 125;
const int SELLER_START_POSITION = 3;

const int SELLER_LEFT_BOUND = 2;
const int SELLER_RIGHT_BOUND = 6;

// Seller's ingredients
const int SELLER_MAXINGREDIENTS_RENDER = 8;
const int SELLER_MAXINGREDIENTS = 20;

// INGREDIENT VARIABLES
const int NUM_INGREDIENTS = 5;

// Ingredient type
enum ingredientType
{
	NOTHING = 0,
	UP_BREAD = 1,
	LETTUCE = 2,
	BEEF = 3,
	TOMATO = 4,
	DOWN_BREAD = 5
};

// Ingredient position
const int INGREDIENTS_DISTANCE = 20;

const int INGREDIENTS_STARTX[] = {125, 250, 375, 500, 625, 750, 875, 1000, 1125};
const int INGREDIENTS_STARTY = SELLER_STARTY - 225;

// DISHES VARIABLES
const int NUM_DISHES = 5;

// Dishes position
const int DISHES_POSX[] = {375, 500, 625, 750, 875};
const int DISHES_POSY = 400;
const int DISHES_FIRST_POSITION = 2;
const int DISHES_LAST_POSITION = 6;

const int DISHES_MAX_INGREDIENTS = 20;
const int DISHES_LIMIT_INGREDIENTS = 12;

// HUNGRY CAT VARIABLES
// Hungry cat position
const int HUNGRYCAT_START_POSX = 100;
const int HUNGRYCAT_START_POSY = INGREDIENTS_STARTY;

const int HUNGRYCAT_END_POSX = INGREDIENTS_STARTX[0];
const int HUNGRYCAT_END_POSY = 600;

const int HUNGRYCAT_POSITION = 0;

const float HUNGRYCAT_EATING_TIME[] = {0, 1, 1, 2, 2, 3};

// COLORS
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color YELLOW = {255, 255, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color ORANGE = {255, 165, 0, 255};
const SDL_Color PINK = {255, 192, 203, 255};
const SDL_Color TRANSPARENT = {0, 0, 0, 0};

