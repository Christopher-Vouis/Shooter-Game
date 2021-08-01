class Bullet;
class Player;
class Enemy;
class Game;
class HitBox;
#pragma once
#include "Graphic.h"
#include "HitBox.h"
#include <vector>
#include "GameEvents.h"
#include "Animation.h"

class GameObject
{
protected:
	std::vector<Graphic> sprites;
	Graphic* currentSprite;
	SDL_Point position;
	HitBox* hitBox;

public:
	virtual void HandleEvents(SDL_Event e) {};
	virtual void HandleCollision(GameObject* collision) {};
	virtual void Cycle() {};
	virtual HitBox *GetHitBox() { return hitBox; }
	Graphic GetGraphic() { return  *currentSprite; }
	std::vector<Graphic> GetGraphics() { return  sprites; }


	enum directions
	{
		NONE = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8
	};

	virtual void SetPosition(int x, int y)
	{
		position = { x, y };
		currentSprite->SetPosition(x, y);
	}

	virtual void MoveObject(int x, int y)
	{
		currentSprite->Move(x, y);
		position = currentSprite->Pos();
	}

	GameObject() {};
	GameObject(Graphic sprite)
	{
		sprites.push_back(sprite);
		currentSprite = &sprites.at(0);
	}
	virtual ~GameObject() 
	{
		SDL_Event* event = new SDL_Event();
		event->type = SDL_USEREVENT;
		event->user.code = gameEvents::REMOVE_COLLIDER;
		event->user.data1 = hitBox;
		SDL_PushEvent(event);
	};
};

