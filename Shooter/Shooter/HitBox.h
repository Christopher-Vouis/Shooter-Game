#pragma once
#include "GameObject.h"
#include <vector>

class GameObject;

class HitBox
{
	SDL_Rect box;
	std::vector<GameObject*> collisions;
	GameObject* object;

public:
	HitBox()
	{
		object = nullptr;
		box = { 0,0,0,0 };
	}
	HitBox(GameObject* obj, SDL_Rect inBox)
	{
		if (obj)
		{
			object = obj;
			box = inBox;
		}
		else
		{
			throw SDL_Error;
		}

	}

	bool AddCollision(GameObject* col)
	{
		for (int i = 0; i < collisions.size(); ++i)
		{
			if (collisions.at(i) == col)
			{
				return false;
			}
		}

		collisions.push_back(col);
		return true;
	}

	bool RemoveCollision(GameObject* col)
	{
		for (int i = 0; i < collisions.size(); ++i)
		{
			if (collisions.at(i) == col)
			{
				collisions.erase(collisions.begin() + i);
				return true;
			}
		}

		return false;
	}

	SDL_Rect GetBox()
	{
		return box;
	}

	void Move(int xDist, int yDist)
	{
		box.x += xDist;
		box.y += yDist;
	}

	GameObject* GetObject()
	{
		return object;
	}
};

