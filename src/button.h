#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "ui.h"

class Button : public UserInterface
{
public:
	Button(const SDL_Rect &rect, const SDL_Color &color, TTF_Font *const font, const SDL_Color &fontColor);

	bool isMouseInside(const int &x, const int &y) const;
	void changeColor(const SDL_Color &color);

private:
	SDL_Point position;
};