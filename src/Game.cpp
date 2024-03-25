#include "Game.h"

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

void Game::handlePlayEvent(SDL_Renderer *renderer, SDL_Event &event)
{
    //if(event.type == SDL_KEYDOWN)
    /*.....*/
}

void Game::play(SDL_Renderer *renderer)
{
    Uint32 frameStart, frameTime;

    gameReset();

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        frameStart = SDL_GetTicks();

        //Handle events on queue
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameState = QUIT;
                break;
            }

            handlePlayEvent(renderer, event);
        }

        //Clear screen
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

        // Change state
		if (live == 0)
		{
			gameState = LOSE;

			//Mix_PlayChannel(-1, loseSound, 0);
		}

        // Quit
		if (gameState != PLAY)
			quit = true;
    }  
}

void Game::menuReset()
{
    /*
    if (musicState)
		Mix_PlayMusic(music, -1);

	if (soundState)
		Mix_Resume(-1);
    */
}

void Game::menu(SDL_Renderer *renderer)
{
    Uint32 frameStart, frameTime;

	menuReset();
    SDL_Event event;
	bool quit = false;
    while(!quit)
    {
        frameStart = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameState = QUIT;
                break;

            case SDL_MOUSEMOTION:
                /*...*/
                break;

            case SDL_MOUSEBUTTONDOWN:
                /*...*/
                break;

            case SDL_MOUSEBUTTONUP:
                /*...*/
                break;
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
		if (gameState != MENU)
			quit = true;
    }
}

void Game::help(SDL_Renderer *renderer)
{
	Uint32 frameStart, frameTime;

	SDL_Event event;
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

void Game::lose(SDL_Renderer *renderer)
{
	Uint32 frameStart, frameTime;

	//updateHighestScore();
	//readHighestScore();

	//Mix_HaltMusic();

	SDL_Event event;
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
void Game::manageState(SDL_Renderer *renderer)
{
	while (loop)
	{
		switch (gameState)
		{
		case MENU:
			menu(renderer);
			break;
		case HELP:
			help(renderer);
			break;
		case PLAY:
			play(renderer);
			break;
		case LOSE:
			lose(renderer);
			break;
		case QUIT:
			loop = false;
			break;
		}
	}
}