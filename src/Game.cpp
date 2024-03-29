#include "Game.h"
#include "Res.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Manager manager;

auto &snake(manager.addEntity());
Game::Game()
{
	gameState = MENU;
}
Game::~Game()
{
	gameState = QUIT;
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

	/*...*/
}

void Game::handlePlayEvent()
{
	SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:

			break;
		case SDLK_DOWN:

			break;
		case SDLK_LEFT:

			break;
		case SDLK_RIGHT:

			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			break;
		case SDLK_DOWN:
			break;
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			break;
		}
	}
}

void Game::play()
{
	Uint32 frameStart, frameTime;

	gameReset();

	bool quit = false;
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

			handlePlayEvent();
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		// Render
		gameground.render(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

		// Update screen
		SDL_RenderPresent(renderer);

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
		background.render(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);

		if (musicState == ON)
			musicOn.render(renderer, MUSIC_POSX, MUSIC_POSY, MUSIC_WIDTH, MUSIC_HEIGHT, NULL);
		else
			musicOff.render(renderer, MUSIC_POSX, MUSIC_POSY, MUSIC_WIDTH, MUSIC_HEIGHT, NULL);

		if (soundState == ON)
			soundOn.render(renderer, SOUND_POSX, SOUND_POSY, SOUND_WIDTH, SOUND_HEIGHT, NULL);
		else
			soundOff.render(renderer, SOUND_POSX, SOUND_POSY, SOUND_WIDTH, SOUND_HEIGHT, NULL);

		title.render(renderer, SCREEN_WIDTH / 2 - title.getWidth() / 2, SCREEN_HEIGHT / 2 - title.getHeight() / 2 - 200, title.getWidth(), title.getHeight(), NULL);

		version.render(renderer, SCREEN_WIDTH - version.getWidth() - 10, 10, version.getWidth(), version.getHeight(), NULL);

		for (int i = 0; i < NUM_BUTTONS; i++)
		{
			buttons[i].render(renderer);
		}

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