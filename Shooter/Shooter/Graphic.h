#pragma once
#include<SDL.h>
class Graphic
{
protected:
	SDL_Rect _rect;
	SDL_Surface _surface;

public:
	virtual SDL_Surface Surface() { return _surface; }
	virtual SDL_Rect Rect() { return _rect; }


	virtual int* Pos() 
	{
		int pos[]{ _rect.x, _rect.y };
		return pos;
	}

	virtual void Move(int xDist, int yDist)
	{
		_rect.x += xDist;
		_rect.y += yDist;
	}

	virtual void SetPosition(int x, int y)
	{
		_rect.x = x;
		_rect.y = y;
	}

	Graphic()
	{

	}

	Graphic(SDL_Surface surf, int xPos, int yPos, int width, int height)
	{
		_rect = SDL_Rect{xPos, yPos, width, height};
		_surface = surf;
	}
};

