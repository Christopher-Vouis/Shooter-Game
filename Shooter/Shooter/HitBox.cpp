#include "HitBox.h"
HitBox::HitBox()
{
	object = nullptr;
	box = { 0,0,0,0 };
}

HitBox::HitBox(GameObject* obj, SDL_Rect inBox)
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

bool HitBox::AddCollision(GameObject* col)
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

bool HitBox::RemoveCollision(GameObject* col)
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

SDL_Rect HitBox::GetBox()
{
	return box;
}

void HitBox::Move(int xDist, int yDist)
{
	box.x += xDist;
	box.y += yDist;
}

void HitBox::SetPosition(int x, int y)
{
	box.x = x;
	box.y = y;
}

GameObject* HitBox::GetObject()
{
	return object;
}