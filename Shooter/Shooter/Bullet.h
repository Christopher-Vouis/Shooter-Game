#pragma once
#include "GameObject.h"
#include "Game.h"

class Bullet : public GameObject
{
	Graphic graphic;
	float vectorX, vectorY, moveProgressX, moveProgressY;
	float moveSpeed = 3;
	SDL_Point step;
	SDL_Surface windowSurf;

	SDL_Surface GetWindowSurf();

public:
	Bullet(SDL_Point point, int angle)
	{
		windowSurf = Game::GetWindowSurf();
		float radians = angle * (M_PI / 180);
		sprites.push_back(Graphic(*IMG_Load("img//cowboy//shot.png"), point.x, point.y, 16, 2, angle, { 8,1 }));
		currentSprite = &sprites.at(0);
		vectorX = cos(radians);
		vectorY = sin(radians);
	};

	void Cycle()
	{
		Move();

		if (currentSprite->Pos().x + currentSprite->Rect().w < 0 ||
			currentSprite->Pos().x > windowSurf.w ||
			currentSprite->Pos().y + currentSprite->Rect().h < 0 ||
			currentSprite->Pos().y > windowSurf.h)
		{
			SDL_Event* event = new SDL_Event();
			event->type = SDL_USEREVENT;
			event->user.code = gameEvents::DESPAWN;
			event->user.data1 = this;
			SDL_PushEvent(event);
		}
	}

	void Move()
	{
		moveProgressX += moveSpeed *  vectorX;
		moveProgressY += moveSpeed *  vectorY;

		if (abs(moveProgressX) >= 1.0)
		{
			step.x = moveProgressX;
			moveProgressX = fmod(moveProgressX, 1);
		}

		if (abs(moveProgressY) >= 1.0)
		{
			step.y = moveProgressY;
			moveProgressY = fmod(moveProgressY, 1);
		}

		if (step.x != 0 || step.y != 0)
		{
			MoveObject(step.x, step.y);
			step = { 0, 0 };
		}
	}
};

