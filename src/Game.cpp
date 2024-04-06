#include "Game.h"
#include "Res.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Manager manager;
std::vector<ColliderComponent *> Game::colliders;
double cnt = 0, id = 0;
SDL_Rect snakeClips[8];
bool renderSnake = false;

Game::Game()
{
	gameState = MENU;
}
Game::~Game()
{
	gameState = QUIT;
}

bool Game::init()
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

void Game::load()
{

	// Load music
	{
		loadMusic(music, "assets/sound/song_suitable_snake.ogg");
		/*loadSound(clickSound, "assets/sounds/click_sound.wav");
		loadSound(leaveSound, "assets/sounds/leave_sound.wav");
		loadSound(levelSound, "assets/sounds/level_sound.wav");
		loadSound(loseSound, "assets/sounds/lose_sound.wav");
		loadSound(receiveSound, "assets/sounds/receive_sound.wav");
		loadSound(wasteSound, "assets/sounds/waste_sound.wav");
		loadSound(warningSound, "assets/sounds/warning_sound.wav");*/
	}

	// Load font
	{
		loadFont(menuFont, "assets/font/india snake pixel labyrinth game_3d.otf", MENU_SIZE);
		loadFont(titleFont, "assets/font/Snake Chan.ttf", TITLE_SIZE);
		loadFont(versionFont, "assets/font/SNAKV___.ttf", VERSION_SIZE);
		/*loadFont(scoreFont, "assets/fonts/version.ttf", SCORE_SIZE);
		loadFont(highestScoreFont, "assets/fonts/version.ttf", HIGHEST_SCORE_SIZE);*/
	}

	// Load images
	{
		loadImage(renderer, background, "assets/background/background.png");
		// loadImage(renderer, helpground, "assets/images/helpground.png");
		// loadImage(renderer, musicOn, "assets/icons/musicOn.png");
		loadImage(renderer, musicOn, "assets/button/Regular_03.png");
		// loadImage(renderer, musicOff, "assets/icons/musicOff.png");
		loadImage(renderer, musicOff, "assets/button/Disable_03.png");
		loadImage(renderer, gameground, "assets/background/gameground.png");
		loadImage(renderer, groundFruit, "assets/background/groundFruit.png");
		loadImage(renderer, snake, "assets/character/1x/snake_done.png");
		for(int i = 0; i < 48; i++)
		{
			const char *head = "assets/snake animation(no bg)/snake(";
			const char *tail = ").png";
			char *path = new char[strlen(head) + strlen(tail) + 2];
			std::string num = "";
			if(i < 10) {
				num = "0";
				num = num + char(i + '0');
			}
			else {
				int x = i;
				num = num +  char(x%10 + '0');
				x/=10;
				num = char(x%10 + '0') + num;
			}
			const char* id = num.c_str();
			std::cout << id << '\n';
			strcpy(path, head);
			strcat(path, id);
			strcat(path, tail);
		 	loadImage(renderer, snakeCute[i], path);
		}
		// loadImage(renderer, stand, "assets/images/stand.png");
		// loadImage(renderer, loseground, "assets/images/loseground.png");
		// loadImage(renderer, heart, "assets/images/heart.png");
		/*
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
	*/
	}
	// Load texts
	title.loadFromRenderedText(WINDOW_TITLE, WHITE, titleFont);
	version.loadFromRenderedText(VERSION_INFO, WHITE, versionFont);

	// Load buttons
	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		SDL_Rect rect = {SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + i * (BUTTON_HEIGHT + 50), BUTTON_WIDTH, BUTTON_HEIGHT};
		Button button(rect, BROWN, menuFont, WHITE);
		button.loadTexture(renderer, menuText[i]);

		buttons.push_back(button);
	}

	for (int i = 0; i < 5; i++)
		snakeClips[i] = {i * 1600, 0, 1600, 1600};
		
}

void Game::setGameState(const int &state)
{
	gameState = state;
}

void Game::gameReset()
{
	score = 0;

	level = MIN_LEVEL;

	live = START_LIVE;

	manager.refresh();

	/*...*/
}

void Game::handlePlayEvent()
{
	// SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			renderSnake = true; cnt = 0;
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			renderSnake = true; cnt = 0;
			break;
		}
	}
	// manager.update();
	// manager.draw();
}

void Game::play()
{
	Uint32 frameStart, frameTime;

	gameReset();
	int posGx = 0;

	bool quit = false;
	// Angle of rotation
	double degrees = 0;

	// Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	while (!quit)
	{
		frameStart = SDL_GetTicks();

		// Handle events on queue
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameState = QUIT;
				break;
			/*case SDL_KEYDOWN:
				 switch( event.key.keysym.sym )
                        {
							case SDLK_SPACE:
							    renderSnake = true;
								break;
                            /*case SDLK_a:
                            degrees -= 60;
                            break;
                            
                            case SDLK_d:
                            degrees += 60;
                            break;

                            case SDLK_q:
                            flipType = SDL_FLIP_HORIZONTAL;
                            break;

                            case SDLK_w:
                            flipType = SDL_FLIP_NONE;
                            break;

                            case SDLK_e:
                            flipType = SDL_FLIP_VERTICAL;
                            break;
                        }*/
			}
			handlePlayEvent();
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render
		gameground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		groundFruit.render(posGx, 555, 289*1.5, 112*1.5, NULL);
		//snake.render(SCREEN_WIDTH - 500, 220, 567, 422, NULL, degrees, NULL, flipType);
		int id;
		if (renderSnake)
		{
			id = (int) cnt/5;
		}
		else id = 0;
		SDL_Rect *currentClip = &snakeClips[id];
	    snake.render(SCREEN_WIDTH - 220*1.5, SCREEN_HEIGHT - 350*1.5, 250*1.5, 250*1.5, currentClip, NULL);
	
		std::cout << "Successful render snake " << cnt << '\n';
		// Update screen
		SDL_RenderPresent(renderer);

		// Frame rate
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}

		posGx += 5;
		cnt += 0.8;
		if (cnt >= 25)
			{
				cnt = 0;
				renderSnake = false;
			}
		if (posGx >= SCREEN_WIDTH)
			posGx = 0;

		// Change state
		if (live == 0)
		{
			gameState = LOSE;

			// Mix_PlayChannel(-1, loseSound, 0);
		}

		// Quit
		if (gameState != PLAY)
			quit = true;
	}
}

void Game::menuReset()
{
	if (musicState)
		Mix_PlayMusic(music, -1);

	// if (soundState)
	//	Mix_Resume(-1);
}

void Game::menu()
{
	Uint32 frameStart, frameTime;

	musicState = ON;
	menuReset();
	double id = 0;
	bool quit = false;
	while (!quit)
	{
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameState = QUIT;
				break;

			case SDL_MOUSEMOTION:
				for (int i = 0; i < NUM_BUTTONS; i++)
				{
					if (buttons[i].isMouseInside(event.motion.x, event.motion.y))
					{
						buttons[i].changeColor(SAND);
					}
					else
					{
						buttons[i].changeColor(BROWN);
					}
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				for (int i = 0; i < NUM_BUTTONS; i++)
				{
					if (buttons[i].isMouseInside(event.motion.x, event.motion.y))
					{
						buttons[i].changeColor(SAND);
						if (soundState == ON)
							Mix_PlayChannel(-1, clickSound, 0);
					}
				}

				if (musicButton.isMouseInside(event.motion.x, event.motion.y))
				{
					if (Mix_PausedMusic() == 1)
					{
						Mix_ResumeMusic();
						musicState = ON;
					}
					else
					{
						Mix_PauseMusic();
						musicState = OFF;
					}
				}

				if (soundButton.isMouseInside(event.motion.x, event.motion.y))
				{
					if (soundState == ON)
					{
						Mix_Pause(-1);
						soundState = OFF;
					}
					else
					{
						Mix_Resume(-1);
						soundState = ON;
					}
				}
				break;

			case SDL_MOUSEBUTTONUP:
				for (int i = 0; i < NUM_BUTTONS; i++)
				{
					if (buttons[i].isMouseInside(event.motion.x, event.motion.y))
					{
						buttons[i].changeColor(SAND);
						switch (i)
						{
						case 0:
							gameState = PLAY;
							break;
						case 1:
							gameState = HELP;
							break;
						case 2:
							gameState = QUIT;
							break;
						}
					}
					else
					{
						buttons[i].changeColor(BROWN);
					}
				}
				break;
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render
		background.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

		if (musicState == ON)
			musicOn.render(MUSIC_POSX, MUSIC_POSY, MUSIC_WIDTH, MUSIC_HEIGHT, NULL);
		else
			musicOff.render(MUSIC_POSX, MUSIC_POSY, MUSIC_WIDTH, MUSIC_HEIGHT, NULL);

		if (soundState == ON)
			soundOn.render(SOUND_POSX, SOUND_POSY, SOUND_WIDTH, SOUND_HEIGHT, NULL);
		else
			soundOff.render(SOUND_POSX, SOUND_POSY, SOUND_WIDTH, SOUND_HEIGHT, NULL);

		title.render(SCREEN_WIDTH / 2 - title.getWidth() / 2, SCREEN_HEIGHT / 2 - title.getHeight() / 2 - 200, title.getWidth(), title.getHeight(), NULL);

		version.render(SCREEN_WIDTH - version.getWidth() - 10, 10, version.getWidth(), version.getHeight(), NULL);

		for (int i = 0; i < NUM_BUTTONS; i++)
		{
			buttons[i].render(renderer);
		}
		
	    snakeCute[(int)id].render(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 250, 250, 250, NULL);
		
		id += 0.3;
		if(id > 47) id = 0;
		// Update screen
		SDL_RenderPresent(renderer);

		// Frame rate
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}

		// Quit
		if (gameState != MENU)
			quit = true;
	}
}

void Game::help()
{
	Uint32 frameStart, frameTime;

	bool quit = false;
	while (!quit)
	{
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameState = QUIT;
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					gameState = MENU;
					break;
				case SDLK_SPACE:
					gameState = PLAY;
					break;
				}
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render

		// Update screen
		SDL_RenderPresent(renderer);

		// Frame rate
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}

		// Quit
		if (gameState != HELP)
			quit = true;
	}
}

void Game::lose()
{
	Uint32 frameStart, frameTime;

	// updateHighestScore();
	// readHighestScore();

	// Mix_HaltMusic();

	bool quit = false;
	while (!quit)
	{
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameState = QUIT;
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					gameState = QUIT;
				case SDLK_SPACE:
					gameState = MENU;
					break;
				}
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render

		// Update screen
		SDL_RenderPresent(renderer);

		// Frame rate
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}

		// Quit
		if (gameState != LOSE)
			quit = true;
	}
}

// manage all states of the game
void Game::manageState()
{
	while (loop)
	{
		switch (gameState)
		{
		case MENU:
			menu();
			break;
		case HELP:
			help();
			break;
		case PLAY:
			play();
			break;
		case LOSE:
			lose();
			break;
		case QUIT:
			loop = false;
			break;
		}
	}
}

void Game::quit()
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
