#include "Boundary.h"

void Boundary::HandleCollision(GameObject* collision)
{
	if (!dynamic_cast<Bullet*>(collision))
	{		
	}
}

Boundary::Boundary(SDL_Rect rect)
{
	box = HitBox(this, rect);

	SDL_Event* event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::NEW_COLLIDER;
	event->user.data1 = &box;
	SDL_PushEvent(event);
}