#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture
{
public:
    // Initializes variables
	Texture();

	// Deallocates memory
	~Texture();

    // Loads image at specified path
	bool loadFromFile(std::string path);

    // Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *textFont);

	bool loadString(std::string path, std::string str, TTF_Font *textFont);

    // Deallocates texture
	void free();

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Renders texture at given point
	void render(int x, int y, int width, int height, SDL_Rect *clip, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();	
	int posX, posY;

private:
    // The actual hardware texture
    SDL_Texture *texture;

    // Image dimesions
    int width, height;
};
