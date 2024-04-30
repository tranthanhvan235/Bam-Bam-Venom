#include "ultils.h"

Texture scoreTexture;

int random(const int &min, const int &max)
{
	return rand() % (max - min + 1) + min;
}

void showLive(SDL_Renderer *renderer)
{
	for (int i = 0; i < live; i++)
	{
		heart.render(LIVE_POSX + i * LIVE_DISTANCE, LIVE_POSY, LIVE_WIDTH, LIVE_HEIGHT, NULL);
	}
}

void showScore(SDL_Renderer *renderer)
{
	SDL_Color textColor = WHITE;
	std::string scoreText = "Score: " + std::to_string(score);
	scoreTexture.loadFromRenderedText(scoreText, textColor, scoreFont);
	scoreTexture.render(SCORE_POSX, SCORE_POSY, scoreTexture.getWidth(), scoreTexture.getHeight(), NULL);
}

void readHighestScore()
{
	std::ifstream file;
	file.open("assets/highestScore.txt");

	if (file.is_open())
		file >> highestScore;

	file.close();
}

void updateHighestScore()
{
	if (score > highestScore)
	{
		highestScore = score;
		std::ofstream file;
		file.open("assets/highestScore.txt");

		if (file.is_open())
			file << highestScore;

		file.close();
	}
}

void showHighestScore(SDL_Renderer *renderer)
{
	SDL_Color textColor = WHITE;
	std::string highestScoreText = "Your score: " + std::to_string(score) + "           ";
	highestScoreText += "Highest Score: " + std::to_string(highestScore);
	scoreTexture.loadFromRenderedText(highestScoreText, textColor, highestScoreFont);

	const int HIGHEST_SCORE_POSX = SCREEN_WIDTH / 2 - scoreTexture.getWidth() / 2;
	const int HIGHEST_SCORE_POSY = SCREEN_HEIGHT / 2 + 100;
	scoreTexture.render(HIGHEST_SCORE_POSX, HIGHEST_SCORE_POSY, scoreTexture.getWidth(), scoreTexture.getHeight(), NULL);
}

int levelUp()
{
	if (score >= LEVEL_POINT[level] && level == MAX_LEVEL)
	{
		level++;
		Mix_PlayChannel(-1, externalTime, 0);
		return 1;
	}

	if (score >= LEVEL_POINT[level] && level < MAX_LEVEL)
	{
		level++;
		Mix_PlayChannel(-1, levelSound, 0);
		return 1;
	}
	return 0;
}