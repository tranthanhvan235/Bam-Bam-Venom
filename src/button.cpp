#include "button.h"

Button::Button(const SDL_Rect &rect, const SDL_Color &color, TTF_Font *const font, const SDL_Color &fontColor)
	: UserInterface(rect, color, font, fontColor)
{
}

/***
	Args:
		x (int): x-coordinate of mouse
		y (int): y-coordinate of mouse
	Returns:
		bool: true if mouse is inside button, false otherwise
***/
bool Button::isMouseInside(const int &x, const int &y) const
{
	// Assume mouse is inside tile
	bool inside = true;

	// Mouse is left of the button
	if (x < mRect.x)
	{
		inside = false;
	}
	// Mouse is right of the button
	else if (x > mRect.x + mRect.w)
	{
		inside = false;
	}
	// Mouse above the button
	else if (y < mRect.y)
	{
		inside = false;
	}
	// Mouse below the button
	else if (y > mRect.y + mRect.h)
	{
		inside = false;
	}

	return inside;
}

/***
	Args:
		color (SDL_Color): a color
	Returns:
		None
***/
void Button::changeColor(const SDL_Color &color)
{
	mColor = color;
}