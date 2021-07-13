#pragma once
#include "Graphic.h"
#include "HitBox.h"

class GameObject
{
protected:
	Graphic* currentSprite;

public:
	virtual void HandleEvents(SDL_Event e) {};
	virtual void HandleCollision(GameObject* collision) {};
	GameObject() {};
};

