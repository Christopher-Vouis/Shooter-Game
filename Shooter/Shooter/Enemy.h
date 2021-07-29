#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
	HitBox* hitBox;
	Animation* animation;

public:
	Enemy()
	{
		sprites.push_back(Graphic());
		currentSprite = &sprites.at(0);
		*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), 300, 500, 96, 96);
		hitBox = new HitBox(static_cast<GameObject*>(this), { currentSprite->Rect().x, currentSprite->Rect().y + 30, 96, 44 });
		std::string walkFrames[2]{ "img\\snake1.png","img\\snake2.png" };
		animation = new Animation(walkFrames, 2, 30);
	}

	~Enemy()
	{
		delete hitBox;
	}

	void Cycle()
	{
		animation->Cycle();
		currentSprite->SetSurface(animation->GetSurface());
	}

	HitBox* GetHitBox()
	{
		return hitBox;
	}
};

