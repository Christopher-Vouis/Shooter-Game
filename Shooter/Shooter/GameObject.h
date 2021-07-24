class Bullet;
class Player;
class Enemy;
class Game;
#pragma once
#include "Graphic.h"
#include "HitBox.h"
#include <vector>
#include "GameEvents.h"

class GameObject
{
protected:
	std::vector<Graphic> sprites;
	Graphic* currentSprite;

public:
	virtual void HandleEvents(SDL_Event e) {};
	virtual void HandleCollision(GameObject* collision) {};
	virtual void Cycle() {};
	Graphic GetGraphic() { return  *currentSprite; }
	std::vector<Graphic> GetGraphics() { return  sprites; }

	virtual void SetPosition(int x, int y)
	{
		currentSprite->SetPosition(x, y);
	}

	virtual void MoveObject(int x, int y)
	{
		currentSprite->Move(x, y);
	}

	GameObject() {};
	GameObject(Graphic sprite)
	{
		sprites.push_back(sprite);
		currentSprite = &sprites.at(0);
	}
};

