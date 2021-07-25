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
	HitBox();
	HitBox(GameObject* obj, SDL_Rect inBox);
	bool AddCollision(GameObject* col);
	bool RemoveCollision(GameObject* col);
	SDL_Rect GetBox();
	void Move(int xDist, int yDist);
	void SetPosition(int x, int y);
	GameObject* GetObject();
};

