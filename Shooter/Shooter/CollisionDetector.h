#pragma once
#include "HitBox.h"
#include "GameEvents.h"
#include <vector>

class CollisionDetector
{
	std::vector<HitBox*> hitBoxes;
	SDL_Event event;
	HitBox* box1, *box2;

	bool AreColliding(SDL_Rect first, SDL_Rect second)
	{
		if (((first.x + first.w) >= second.x) && ((second.x + second.w >= first.x)) 
			&& ((first.y + first.h) >= second.y) && ((second.y + second.h >= first.y)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

public:
	CollisionDetector()
	{
		event.type = SDL_USEREVENT;
		event.user.code = gameEvents::COLLISION;
		box1 = new HitBox();
		box2 = new HitBox();
	}

	void AddHitBox(HitBox* box)
	{
		hitBoxes.push_back(box);
	}

	void CheckCollisions()
	{
		for(auto box : hitBoxes)
		{
			for (auto otherBox : hitBoxes)
			{
				if (otherBox != box)
				{
					if (AreColliding(box->GetBox(), otherBox->GetBox()))
					{
						*box1 = *box;
						*box2 = *otherBox;
						event.user.data1 = box1;
						event.user.data2 = box2;
						SDL_PushEvent(&event);
						std::cout << "Hit" << std::endl;
					}
				}
			}
		}
	}

	void RemoveHitBox(HitBox* box)
	{
		for (int i = 0; i < hitBoxes.size(); ++i)
		{
			if (hitBoxes.at(i) == box)
			{
				hitBoxes.erase(hitBoxes.begin() + i);
			}
		}
	}
};

