#pragma once
#include "GameObject.h"
#include "Game.h"

class Bullet : public GameObject
{
	Graphic graphic;
	float vectorX, vectorY, moveProgressX, moveProgressY;
	float moveSpeed = 3;
	SDL_Point step;
	SDL_Surface windowSurf;

public:
	Bullet(SDL_Point point, int angle);
	void Cycle();
	void Move();
};

