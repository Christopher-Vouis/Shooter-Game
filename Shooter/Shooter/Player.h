#pragma once
#include "Graphic.h"
#include <vector>
#include <SDL_image.h>

class Player
{
	Graphic* currentSprite;
	std::vector<Graphic> sprites;

public:
	Player()
	{
		sprites.push_back(Graphic(*IMG_Load("img\\cowboy\\cowboy.png"), 500, 500, 96, 96));
		currentSprite = &sprites.at(0);
	}

	std::vector<Graphic> GetSprites()
	{
		return sprites;
	}
};

