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
	int _rotation, _width, _height;
	SDL_RendererFlip _flipMode;

public:
	virtual SDL_Surface Surface() { return _surface; }
	virtual SDL_Rect Rect() { return _rect; }
	virtual SDL_Point Origin() { return _origin; }
	virtual int Rotation() { return _rotation; }
	virtual SDL_Point Pos() {return { _rect.x, _rect.y }; }
	virtual SDL_RendererFlip FlipMode() { return _flipMode; }

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

	void FlipHorizontal()
	{
		if (_flipMode & SDL_FLIP_HORIZONTAL)
		{
			_flipMode = static_cast<SDL_RendererFlip>(~SDL_FLIP_HORIZONTAL & _flipMode);
		}
		else
		{
			_flipMode = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | _flipMode);
		}
	}

	void SetFlipH(bool isFlip)
	{
		if (isFlip)
		{
			_flipMode = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | _flipMode);
		}
		else
		{
			_flipMode = static_cast<SDL_RendererFlip>(~SDL_FLIP_HORIZONTAL & _flipMode);
		}
	}

	void FlipVertical()
	{
		if (_flipMode & SDL_FLIP_VERTICAL)
		{
			_flipMode = static_cast<SDL_RendererFlip>(~SDL_FLIP_VERTICAL & _flipMode);
		}
		else
		{
			_flipMode = static_cast<SDL_RendererFlip>(SDL_FLIP_VERTICAL | _flipMode);
		}
	}

	void SetFlipV(bool isFlip)
	{
		if (isFlip)
		{
			_flipMode = static_cast<SDL_RendererFlip>(SDL_FLIP_VERTICAL | _flipMode);
		}
		else
		{
			_flipMode = static_cast<SDL_RendererFlip>(~SDL_FLIP_VERTICAL & _flipMode);
		}
	}

	void SetFlicker(bool shouldFlicker)
	{
		if (shouldFlicker)
		{
			_rect.w = 0;
			_rect.h = 0;
		}
		else
		{
			_rect.w = _width;
			_rect.h = _height;
		}
	}

	Graphic()
	{

	}

	Graphic(SDL_Surface surf, int xCoord, int yCoord, int width, int height, int degrees = 0, SDL_Point origin = { 0, 0 }, SDL_RendererFlip flipMode = SDL_FLIP_NONE)
	{
		_rect = SDL_Rect{xCoord, yCoord, width, height};
		_width = width;
		_height = height;
		_surface = surf;
		_rotation = degrees;
		_origin = origin;
		_flipMode = flipMode;
	}

	~Graphic()
	{

	}
};

