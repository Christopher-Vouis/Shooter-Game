#pragma once
#include "Enemy.h"
class Snake : public Enemy
{
public:
	Snake(SDL_Rect bounds);
	~Snake();
	void Cycle();
private:
	GameObject::directions ChooseDirection();
	bool isReturning = false;
};

