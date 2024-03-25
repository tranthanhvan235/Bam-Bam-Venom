#include "Res.h"

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
	if (!texture.loadFromFile(renderer, path))
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

bool init(SDL_Window *&window, SDL_Renderer *&renderer)
{
    // Initialization flag
	bool success = true;
    // Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
    else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
		}

		// Create window
		window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Create vsynced renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
					success = false;
				}

				if (TTF_Init() == -1)
				{
					std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
					success = false;
				}
			}
		}
	}

    // Initialise SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialise! Error: " << Mix_GetError() << std::endl;
		success = false;
	}

	return success;

}

void load(SDL_Renderer *&renderer)
{
    /*
	// Load music
	loadMusic(music, "assets/sounds/music.wav");
	loadSound(clickSound, "assets/sounds/click_sound.wav");
	loadSound(leaveSound, "assets/sounds/leave_sound.wav");
	loadSound(levelSound, "assets/sounds/level_sound.wav");
	loadSound(loseSound, "assets/sounds/lose_sound.wav");
	loadSound(receiveSound, "assets/sounds/receive_sound.wav");
	loadSound(wasteSound, "assets/sounds/waste_sound.wav");
	loadSound(warningSound, "assets/sounds/warning_sound.wav");

	// Load font
	loadFont(menuFont, "assets/fonts/menu.ttf", MENU_SIZE);
	loadFont(titleFont, "assets/fonts/title.ttf", TITLE_SIZE);
	loadFont(versionFont, "assets/fonts/version.ttf", VERSION_SIZE);
	loadFont(scoreFont, "assets/fonts/version.ttf", SCORE_SIZE);
	loadFont(highestScoreFont, "assets/fonts/version.ttf", HIGHEST_SCORE_SIZE);

	// Load images
	loadImage(renderer, background, "assets/images/background.png");
	loadImage(renderer, helpground, "assets/images/helpground.png");
	loadImage(renderer, musicOn, "assets/icons/musicOn.png");
	loadImage(renderer, soundOn, "assets/icons/soundOn.png");
	loadImage(renderer, musicOff, "assets/icons/musicOff.png");
	loadImage(renderer, soundOff, "assets/icons/soundOff.png");
	loadImage(renderer, gameground, "assets/images/gameground.png");
	loadImage(renderer, stand, "assets/images/stand.png");
	loadImage(renderer, loseground, "assets/images/loseground.png");
	loadImage(renderer, heart, "assets/images/heart.png");

	customerRight.loadFromFile(renderer, "assets/images/seller/sellerRight.png");
	customerLeft.loadFromFile(renderer, "assets/images/seller/sellerLeft.png");
	customerStand.loadFromFile(renderer, "assets/images/seller/sellerStand.png");

	loadImage(renderer, up_bread, "assets/images/ingredients/up_bread.png");
	loadImage(renderer, lettuce, "assets/images/ingredients/lettuce.png");
	loadImage(renderer, beef, "assets/images/ingredients/beef.png");
	loadImage(renderer, tomato, "assets/images/ingredients/tomato.png");
	loadImage(renderer, down_bread, "assets/images/ingredients/down_bread.png");

	loadImage(renderer, fox, "assets/images/customer/fox.png");
	loadImage(renderer, wolf, "assets/images/customer/wolf.png");
	for (int i = 0; i < CUSTOMER_MOTION_RECTANGLE; i++)
	{
		customerRect[i].x = i * 152;
		customerRect[i].y = 0;
		customerRect[i].w = 134;
		customerRect[i].h = 134;
	}

	loadImage(renderer, talkBubble, "assets/images/customer/talk_bubble.png");

	// Load texts
	title.loadFromRenderedText(renderer, WINDOW_TITLE, ORANGE, titleFont);
	version.loadFromRenderedText(renderer, VERSION_INFO, BLACK, versionFont);

	// Load buttons
	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		SDL_Rect rect = {SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + i * (BUTTON_HEIGHT + 50), BUTTON_WIDTH, BUTTON_HEIGHT};
		Button button(rect, PINK, menuFont, ORANGE);
		button.loadTexture(renderer, menuText[i]);

		buttons.push_back(button);
	}
    */
}

void quit(SDL_Window *&window, SDL_Renderer *&renderer)
{
    // Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;

	// Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
}
