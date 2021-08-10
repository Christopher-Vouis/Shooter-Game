#pragma once
#include "GameObject.h"
#include "Bullet.h"
class Boundary : public GameObject
{
	HitBox box;

public:
	void HandleCollision(GameObject* collision);
	Boundary(SDL_Rect rect);
};
