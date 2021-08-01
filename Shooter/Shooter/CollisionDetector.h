#pragma once
#include "HitBox.h"
#include "GameEvents.h"
#include <vector>

class CollisionDetector
{
	std::vector<HitBox*> hitBoxes;
	SDL_Event event;
	HitBox* box1, *box2;
	SDL_Renderer* renderer;
	SDL_Surface* surface;

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
	CollisionDetector(SDL_Renderer* rend)
	{
		renderer = rend;
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
		for(HitBox* box : hitBoxes)
		{
			DrawHitBox(*box);
			for (HitBox* otherBox : hitBoxes)
			{
				if (otherBox != box)
				{
					if (AreColliding(box->GetBox(), otherBox->GetBox()) && box->GetObject() != otherBox->GetObject())
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
				break;
			}
		}
	}

	void DrawHitBox(HitBox box)
	{
		SDL_SetRenderDrawColor(renderer, 225, 50, 50, 255);
		SDL_Rect b = box.GetBox();
		SDL_RenderDrawRect(renderer, &b);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
};

