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
#include "GameText.h"

class GameObject
{
protected:
	std::vector<Graphic> sprites;	
	std::vector<GameText> texts;
	Graphic* currentSprite;
	SDL_Point position;
	HitBox* hitBox;
	SDL_Rect boundary = { 0,0,0,0 };
	int flickerTimer = 0;
	bool isDead = false, isFlicker = false;

public:
	virtual void HandleEvents(SDL_Event e) {};
	virtual void HandleCollision(GameObject* collision) {};
	virtual void Cycle() {};
	virtual HitBox *GetHitBox() { return hitBox; }
	virtual Graphic GetGraphic() { return  *currentSprite; }
	std::vector<Graphic> GetGraphics() { return  sprites; }
	std::vector<GameText> GetTexts() { return  texts; }

	enum directions
	{
		NONE = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8
	};

	virtual void SetPosition(int x, int y);
	virtual void MoveObject(int x, int y);
	GameObject();
	GameObject(Graphic sprite);
	virtual ~GameObject();
};

