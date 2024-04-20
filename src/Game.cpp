#include "Game.h"
#include "Res.h"
#include "Snake.h"

Game::Game()
{
	gameState = MENU;
	randVel = rand() % 2 + 1.5;
	velFrame = 7;
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
		window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
				SDL_SetRenderDrawColor(renderer, 136, 193, 68, 50);
				SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

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
		loadMusic(music, "assets/sound/song.ogg");
		loadSound(clickSound, "assets/sound/button_push.wav");
		loadSound(music_soundClick, "assets/sound/sound_musicClick.wav");
		loadSound(jumpSound, "assets/sound/jump.wav");
		loadSound(fruitDown, "assets/sound/fruit_down.wav");
		// loadSound(leaveSound, "assets/sounds/leave_sound.wav");
		loadSound(levelSound, "assets/sound/background-audio_script_sound.wav");
		loadSound(varSound, "assets/sound/snake_var.wav");
		loadSound(loseSound, "assets/sound/loseSound.wav");
		loadSound(eatSound, "assets/sound/gotScore.wav");
		loadSound(transSound, "assets/sound/trans.wav");
		// loadSound(wasteSound, "assets/sounds/waste_sound.wav");
		// loadSound(warningSound, "assets/sounds/warning_sound.wav");
	}

	// Load font
	{
		loadFont(menuFont, "assets/font/india snake pixel labyrinth game_3d.otf", MENU_SIZE);
		loadFont(titleFont, "assets/font/Snake Chan.ttf", TITLE_SIZE);
		loadFont(versionFont, "assets/font/SNAKV___.ttf", VERSION_SIZE);
		// loadFont(scoreFont, "assets/font/FunSnake.otf", SCORE_SIZE);
		loadFont(scoreFont, "assets/font/Diane Amorta.otf", SCORE_SIZE);
		loadFont(highestScoreFont, "assets/font/Lovely Kids.ttf", HIGHEST_SCORE_SIZE);
		loadFont(levelUpFont, "assets/font/Groen California Sans.ttf", LEVEL_SIZE);
	}

	// Load images
	{
		loadImage(background, "assets/background/background.png");
		loadImage(backgroundFull, "assets/background/background.png");
		loadImage(helpground, "assets/background/BAMBAM_HELP.png");
		loadImage(soundOn, "assets/menu/soundOn.png");
		loadImage(musicOn, "assets/menu/musicOn.png");
		loadImage(soundOff, "assets/menu/soundOff.png");
		loadImage(musicOff, "assets/menu/musicOff.png");
		loadImage(gameground, "assets/background/gameground.png");
		for (int i = 0; i < 48; i++)
		{
			const char *head = "assets/snake animation(no bg)/snake(";
			const char *tail = ").png";
			char *path = new char[strlen(head) + strlen(tail) + 2];
			std::string num = "";
			if (i < 10)
			{
				num = "0";
				num = num + char(i + '0');
			}
			else
			{
				int x = i;
				num = num + char(x % 10 + '0');
				x /= 10;
				num = char(x % 10 + '0') + num;
			}
			const char *id = num.c_str();
			strcpy(path, head);
			strcat(path, id);
			strcat(path, tail);
			loadImage(snakeCute[i], path);
		}
		// loadImage(renderer, stand, "assets/images/stand.png");
		loadImage(loseground, "assets/background/loseGround.png");
		loadImage(heart, "assets/menu/heart.png");
		/*
		customerRight.loadFromFile(renderer, "assets/images/seller/sellerRight.png");
		customerLeft.loadFromFile(renderer, "assets/images/seller/sellerLeft.png");
		customerStand.loadFromFile(renderer, "assets/images/seller/sellerStand.png");
		*/

		/*
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
	paused.loadFromRenderedText(PAUSED_GAME, WHITE, titleFont);
	LevelUP.loadFromRenderedText(LEVEL_UP, WHITE, levelUpFont);
	// Load buttons
	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		SDL_Rect rect = {SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + i * (BUTTON_HEIGHT + 50), BUTTON_WIDTH, BUTTON_HEIGHT};
		Button button(rect, BROWN, menuFont, WHITE);
		button.loadTexture(renderer, menuText[i]);

		buttons.push_back(button);
	}
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

	isPaused = false;

	randVel = rand() % 2 + 1.5;
	velFrame = 7;
	fruit.clear();

	wood = new Wood();
	int fruitSize = rand() % 5 + 3;

	for (int i = 0; i < fruitSize; i++)
	{
		Fruit *newFruit = new Fruit();
		if (fruit.size())
		{
			newFruit->posX = fruit[fruit.size() - 1]->posX - newFruit->getWidth() - (i + 1) * rand() % 20;
			newFruit->posY = fruit[fruit.size() - 1]->posY - newFruit->getHeight() * i;
		}
		fruit.push_back(newFruit);
	}
}

void Game::handlePlayEvent()
{
	// SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:

			break;
		}
	}
}

int Game::checkCollision()
 {
	Collision curCol = wood->getCol(1);
	Collision snakeCol = snake->getCol();
	//return 0;
	
	//std::cout << snake->frame << '\n';
	return 0;
	// for (int i = 0; i < fruit.size(); i++)
	// 	if (fruit[i]->checkCollision(curCol))
	// 	{
	// 		snake->frame = 0;
	// 		snake->goingUp = true;
	// 		//fruit.erase(fruit.begin() + i);
	// 		return 1;
	// 	}
	
	// if (wood->checkCollision(curCol))
	// {
	// 	Mix_PlayChannel(-1, varSound, 0);
	// 	return 2;
	// }
	// return 0;
}
void Game::renderUpLevel()
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetRenderDrawColor(renderer, 132, 78, 51, 255);
	SDL_RenderClear(renderer);

	// Render
	gameground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

	showScore(renderer);
	showLive(renderer);

	LevelUP.render(SCREEN_WIDTH / 2 - LevelUP.getWidth() / 2, SCREEN_HEIGHT / 2 - LevelUP.getHeight() / 2, LevelUP.getWidth(), LevelUP.getHeight(), NULL);
	//  Update screen
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
}

void Game::play()
{
	Uint32 frameStart, frameTime;
	Snake *snake = new Snake();

	gameReset();

	bool quit = false;
	int id = 1;
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
			}
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					gameState = MENU;
					break;

				case SDLK_p:
					isPaused = isPaused xor 1;
					break;

				case SDLK_SPACE:
				case SDLK_DOWN:
					if (isPaused)
						break;
					if (!snake->goingDown && !snake->goingUp)
						snake->goingDown = true;
					//if (snake->frame == 0 && !snake->goingDown)
					//	if (soundState)
					//		Mix_PlayChannel(-1, jumpSound, 0);
					break;
				}
			}
			// handlePlayEvent();
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_SetRenderDrawColor(renderer, 132, 78, 51, 255);
		SDL_RenderClear(renderer);

		// Render
		gameground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

		wood->generate(isPaused);
		for (auto &eFruit : fruit)
			eFruit->generate(isPaused);
		snake->render(isPaused);

		if (checkCollision() == 2)
			live--;

		showScore(renderer);
		showLive(renderer);

		if (isPaused)
			paused.render(SCREEN_WIDTH / 2 - paused.getWidth() / 2, SCREEN_HEIGHT / 2 - paused.getHeight() / 2, paused.getWidth(), paused.getHeight(), NULL);

		//  Update screen
		SDL_RenderPresent(renderer);

		if (levelUp())
		{
			//renderUpLevel();
			randVel++;
			velFrame -= 0.5;
		}
		// Frame rate
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}

		// Change state
		if (live == 0)
		{
			gameState = LOSE;
			Mix_PlayChannel(-1, loseSound, 0);
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

	if (soundState)
		Mix_Resume(-1);
	isPaused = false;
}

void Game::menu()
{
	Uint32 frameStart, frameTime;

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
						curId = i;
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
						curId = i;
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
					Mix_PlayChannel(-1, music_soundClick, 0);
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
					Mix_PlayChannel(-1, music_soundClick, 0);
				}
				break;

			case SDL_MOUSEBUTTONUP:
				for (int i = 0; i < NUM_BUTTONS; i++)
				{
					if (buttons[i].isMouseInside(event.motion.x, event.motion.y))
					{
						buttons[i].changeColor(SAND);
						curId = i;
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

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
				case SDLK_w:
					buttons[curId].changeColor(BROWN);
					if (curId > 0)
					{
						curId--;
						if (soundState == ON)
							Mix_PlayChannel(-1, transSound, 0);
					}
					buttons[curId].changeColor(SAND);

					break;

				case SDLK_DOWN:
				case SDLK_s:
					buttons[curId].changeColor(BROWN);
					if (curId + 1 < NUM_BUTTONS)
					{
						curId++;
						if (soundState == ON)
							Mix_PlayChannel(-1, transSound, 0);
					}
					buttons[curId].changeColor(SAND);

					break;
				}

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_KP_ENTER:
				case SDLK_RETURN:
					buttons[curId].changeColor(SAND);
					if (soundState == ON)
						Mix_PlayChannel(-1, clickSound, 0);
					switch (curId)
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
					break;
				}
			}

			// Clear screen
			SDL_SetRenderDrawColor(renderer, 136, 193, 68, 50);
			SDL_RenderClear(renderer);

			// Render
			// backgroundFull.render(0, 0, 2000, 2000, NULL);
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

			id += 0.5;
			if (id > 47)
				id = 0;
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
					if (soundState)
						Mix_PlayChannel(-1, clickSound, 0);
					break;
				case SDLK_SPACE:
					// isPaused = true;
					gameState = PLAY;
					if (soundState)
						Mix_PlayChannel(-1, clickSound, 0);
					break;
				}
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render
		helpground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

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

	updateHighestScore();
	readHighestScore();

	Mix_HaltMusic();

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
					if (soundState)
						Mix_PlayChannel(-1, clickSound, 0);
					break;

				case SDLK_SPACE:
					gameState = MENU;
					if (soundState)
						Mix_PlayChannel(-1, clickSound, 0);
					break;
				}
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render
		loseground.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		showHighestScore(renderer);

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
