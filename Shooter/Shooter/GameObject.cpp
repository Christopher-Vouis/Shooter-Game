#include "GameObject.h"

void GameObject::SetPosition(int x, int y)
{
	position = { x, y };
	if (currentSprite != nullptr)
	{
		currentSprite->SetPosition(x, y);
	}
	if (hitBox != nullptr)
	{
		hitBox->SetPosition(x, y);
	}
}

void GameObject::MoveObject(int x, int y)
{
	currentSprite->Move(x, y);
	position = currentSprite->Pos();
}

GameObject::GameObject()
{
	currentSprite = nullptr;
	hitBox = nullptr;

}

GameObject::GameObject(Graphic sprite)
{
	sprites.push_back(sprite);
	currentSprite = &sprites.at(0);
}

GameObject::~GameObject()
{
	SDL_Event* event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::REMOVE_COLLIDER;
	event->user.data1 = hitBox;
	SDL_PushEvent(event);
};