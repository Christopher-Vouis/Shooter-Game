#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameText.h"
#include "Graphic.h"
#include <vector>
#include "GameEvents.h"
#include "GameObject.h"

class GameMode
{

protected:
	std::vector<GameObject*> objects;
	std::vector<GameText> texts;
	std::vector<Graphic> images;
	Graphic background;
	SDL_Surface* bgSurface;
	SDL_Renderer* renderer;
	SDL_Surface* surface;

public:
	GameMode(SDL_Renderer* rend, SDL_Surface* surf) 
	{
		renderer = rend;
		surface = surf;
		bgSurface = new SDL_Surface();
		*bgSurface = *SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0, 0, 0, 255);
		background = Graphic(*bgSurface, 0, 0, surface->w, surface->h);
	}
	virtual void HandleInputs(SDL_Event e) {};
	virtual void HandleEvents(SDL_Event e) {};
	virtual void Update() {};
	virtual std::vector<GameObject*> GetObjects() {

		return objects;
	}
	virtual std::vector<GameText> GetTexts() {

		return texts;
	}
	virtual  std::vector<Graphic> GetImages() {

		return images;
	}
	virtual Graphic GetBackground()
	{
		return background;
	}
};

