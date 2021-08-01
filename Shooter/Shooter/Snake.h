#pragma once
#include "Enemy.h"
class Snake : public Enemy
{
public:
	Snake(int startX, int startY);
	~Snake();
	void Cycle();
private:
	GameObject::directions ChooseDirection();
};

