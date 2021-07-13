#pragma once
#include<SDL.h>
#include <iostream>
#include <SDL_image.h>
class Graphic
{
protected:
	SDL_Rect _rect;
	SDL_Surface _surface;
	SDL_Point _origin;
	int _rotation;

public:
	virtual SDL_Surface Surface() { return _surface; }
	virtual SDL_Rect Rect() { return _rect; }
	virtual SDL_Point Origin() { return _origin; }
	virtual int Rotation() { return _rotation; }
	virtual SDL_Point Pos() {return { _rect.x, _rect.y }; }

	virtual void Move(int xDist, int yDist)
	{
		_rect.x += xDist;
		_rect.y += yDist;
	}

	virtual void Rotate(int degrees)
	{
		_rotation = degrees;
	}

	virtual void SetPosition(int x, int y)
	{
		_rect.x = x;
		_rect.y = y;
	}

	virtual void SetSurface(SDL_Surface surf)
	{
		_surface = surf;
	}

	Graphic()
	{

	}

	Graphic(SDL_Surface surf, int xCoord, int yCoord, int width, int height, int degrees = 0, SDL_Point origin = { 0, 0 })
	{
		_rect = SDL_Rect{xCoord, yCoord, width, height};
		_surface = surf;
		_rotation = degrees;
		_origin = origin;
	}

	~Graphic()
	{

	}
};

