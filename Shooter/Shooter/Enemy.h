#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
	HitBox* hitBox;

public:
	Enemy(Graphic* graphic)
	{
		currentSprite = graphic;
		*currentSprite = Graphic(*IMG_Load("img\\cowboy\\cowboy.png"), 300, 500, 96, 96);
		hitBox = new HitBox(static_cast<GameObject*>(this), currentSprite->Rect());
	}

	~Enemy()
	{
		delete hitBox;
	}

	HitBox* GetHitBox()
	{
		return hitBox;
	}
};

