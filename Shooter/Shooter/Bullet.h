#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
	Graphic graphic;
	float vectorX, vectorY, moveProgressX, moveProgressY;
	float moveSpeed = 4;
	SDL_Point step;
	SDL_Surface windowSurf;
	HitBox hitBox1, hitBox2;

public:
	Bullet(SDL_Point point, int angle);
	~Bullet();
	void Cycle();
	void Move();
	void ArrangeHitBoxes(int angle);
};

