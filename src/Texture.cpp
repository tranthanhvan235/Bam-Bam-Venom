#include "Texture.h"
#include "Game.h"

SDL_Renderer *Game::renderer;
SDL_Event Game::event;

Texture::Texture()
{
	// Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	// Deallocate
	free();
}

bool Texture::loadFromFile(std::string path)
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Game::renderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	texture = newTexture;
	return texture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *textFont)
{
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(textFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		// Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
		if (texture == NULL)
		{
			std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	// Return success
	return texture != NULL;
}

bool Texture::loadString(std::string path, std::string str, TTF_Font *textFont)
{
	bool success = true;

	// Open the font
	textFont = TTF_OpenFont(path.c_str(), 32);
	if (textFont == NULL)
	{
		std::cout << "Unable to load font " << path << "! SDL_ttf Error: " << TTF_GetError() << std::endl;
		success = false;
	}
	else
	{
		// Render text
		SDL_Color textColor = {0, 0, 0};
		if (!loadFromRenderedText(str, textColor, textFont))
		{
			std::cout << "Unable to render text texture! SDL_ttf Error: " << TTF_GetError() << std::endl;
			success = false;
		}
	}

	return success;
}

void Texture::free()
{
	// Free texture if it exists
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);

		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture rgb
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::render(int x, int y, int width, int height, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, width, height};

	// Set clip rendering dimensions
	// if (clip != NULL)
	// {
	// 	renderQuad.w = clip->w;
	// 	renderQuad.h = clip->h;
	// }

	// Render to screen
	if(SDL_RenderCopyEx(Game::renderer, texture, clip, &renderQuad, angle, center, flip)!= 0)
	{
		std::cout << "! SDL Error: " << SDL_GetError() << std::endl;
	}
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}
