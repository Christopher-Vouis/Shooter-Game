#pragma once
#include "Enemy.h"
class Snake : public Enemy
{
public:
	Snake(SDL_Rect bounds);
	~Snake();
	void Die();
	void Cycle();
	void HandleCollision(GameObject* collision);

	Graphic deathSprite;
	SDL_Event* event;

private:
	GameObject::directions ChooseDirection();
	bool isReturning = false;
};

