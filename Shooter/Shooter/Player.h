#pragma once
#include "Graphic.h"
#include <vector>
#include <SDL_image.h>
#include "Animation.h"
#include <math.h>
#include <iostream>
#include "GameObject.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameEvents.h"

class Player : public GameObject
{
	SDL_Surface idleSurface, armSurface;
	Animation* walkAnim;
	Graphic* arm;
	HitBox* hitBox;

	int hitpoints = 3, xMove, yMove, crosshairX, crosshairY, armAngle;
	bool invincible = false;
	double moveSpeed = 0.75;
	double moveProgress = 0.0;
	const Uint8* keyboardState;
	SDL_Point armPoint, bulletPoint;

	enum directions
	{
		NONE = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8
	};

	enum class playerState
	{
		IDLE,
		WALKING,
		DEAD
	};

	playerState state;
	uint8_t movementDir;

public:
	Player()
	{
		idleSurface = *IMG_Load("img\\cowboy\\cowboy.png");
		armSurface = *IMG_Load("img\\cowboy\\arm.png");
		std::string walkFrames[2]{ "img\\cowboy\\cowboy_walk1.png","img\\cowboy\\cowboy_walk2.png" };
		walkAnim = new Animation(walkFrames, 2, 40);
		sprites.push_back(Graphic());
		sprites.push_back(Graphic());
		arm = &sprites.at(0);
		currentSprite = &sprites.at(1);
		*currentSprite = Graphic(idleSurface, 500, 500, 96, 96);
		*arm = Graphic(armSurface,
			currentSprite->Pos().x + currentSprite->Rect().w / 3,
			currentSprite->Pos().y - 4,
			96, 
			96, 
			0,
			{34, 48}
		);

		armPoint = { currentSprite->Pos().x + arm->Origin().x, currentSprite->Pos().y + arm->Origin().y };
		bulletPoint = { armPoint.x + arm->Rect().w, armPoint.y + arm->Rect().h / 2 };
		state = playerState::IDLE;
		keyboardState = SDL_GetKeyboardState(NULL);

		hitBox = new HitBox(static_cast<GameObject*>(this), currentSprite->Rect());
	}

	~Player()
	{
		delete walkAnim;
		delete currentSprite;
	}

	Graphic GetSprites()
	{
		return *currentSprite;
	}

	HitBox* GetHitBox()
	{
		return hitBox;
	}

	void Cycle()
	{
		if (movementDir == directions::NONE)
		{
			state = playerState::IDLE;
			moveProgress = 0;
		}
		else
		{
			state = playerState::WALKING;
		}

		switch (state)
		{
		case playerState::IDLE:
			currentSprite->SetSurface(idleSurface);
			break;
		case playerState::WALKING:
			walkAnim->Cycle();
			currentSprite->SetSurface(walkAnim->GetSurface());
			Move();
			break;
		case playerState::DEAD:
			break;
		default:
			break;
		}
	}

	void HandleInputs(SDL_Event e)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				Shoot();
			}
		}
		else
		{
			switch (e.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				if (e.type == SDL_KEYDOWN)
				{
					if (!keyboardState[SDL_SCANCODE_S])
					{
						movementDir |= directions::UP;
					}
				}
				else if (e.type == SDL_KEYUP)
				{
					movementDir &= ~directions::UP;
					if (keyboardState[SDL_SCANCODE_S])
					{
						movementDir |= directions::DOWN;
					}
				}
				break;
			case SDL_SCANCODE_S:
				if (e.type == SDL_KEYDOWN)
				{
					if (!keyboardState[SDL_SCANCODE_W])
					{
						movementDir |= directions::DOWN;
					}
				}
				else if (e.type == SDL_KEYUP)
				{
					movementDir &= ~directions::DOWN;
					if (keyboardState[SDL_SCANCODE_W])
					{
						movementDir |= directions::UP;
					}
				}
				break;
			case SDL_SCANCODE_A:
				if (e.type == SDL_KEYDOWN)
				{
					if (!keyboardState[SDL_SCANCODE_D])
					{
						movementDir |= directions::LEFT;
					}
				}
				else if (e.type == SDL_KEYUP)
				{
					movementDir &= ~directions::LEFT;
					if (keyboardState[SDL_SCANCODE_D])
					{
						movementDir |= directions::RIGHT;
					}
				}
				break;
			case SDL_SCANCODE_D:
				if (e.type == SDL_KEYDOWN)
				{
					if (!keyboardState[SDL_SCANCODE_A])
					{
						movementDir |= directions::RIGHT;
					}
				}
				else if (e.type == SDL_KEYUP)
				{
					movementDir &= ~directions::RIGHT;
					if (keyboardState[SDL_SCANCODE_A])
					{
						movementDir |= directions::LEFT;
					}
				}
				break;
			default:
				break;
			}
		}
	}

	void HandleEvents(SDL_Event e)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		case SDL_MOUSEBUTTONDOWN:
			HandleInputs(e);
		case SDL_MOUSEMOTION:
			Aim();
			break;
		default:
			break;
		}
	}

	void HandleCollision(GameObject* collision)
	{
		if (static_cast<Enemy*>(collision))
		{
			TakeDamage(1);
		}
	}

private:
	void Move()
	{
		moveProgress += moveSpeed;

		if (moveProgress > 1.0)
		{
			if (movementDir & directions::UP)
			{
				yMove = -moveProgress;
			}
			else if (movementDir & directions::DOWN)
			{
				yMove = moveProgress;
			}
			else
			{
				yMove = 0;
			}

			if (movementDir & directions::LEFT)
			{
				xMove = -moveProgress;
			}
			else if (movementDir & directions::RIGHT)
			{
				xMove = moveProgress;
			}
			else
			{
				xMove = 0;
			}

			moveProgress -= (int)moveProgress;
			currentSprite->Move(xMove, yMove);
			hitBox->Move(xMove, yMove);
			arm->Move(xMove, yMove);
			armPoint = { armPoint.x + xMove, armPoint.y + yMove };
			bulletPoint = CalculateBulletPoint();
		}
	}

	SDL_Point CalculateBulletPoint()
	{
		double radians = armAngle * (M_PI / 180);
		int x = armPoint.x + sin(radians) * arm->Rect().w;
		int y = armPoint.y + cos(radians) * -arm->Rect().w;
		return {  x, y };
	}

	void Shoot()
	{
		Bullet* bullet = new Bullet(bulletPoint, armAngle - 90);
		SDL_Event* event = new SDL_Event();
		event->type = SDL_USEREVENT;
		event->user.code = gameEvents::SPAWN;
		event->user.data1 = bullet;
		SDL_PushEvent(event);
	}

	void Aim()
	{
		armAngle = -GetCursorAngle();
		if (armAngle < 0)
		{
			SetFlipH(true);
		}
		else
		{
			SetFlipH(false);
		}
		arm->Rotate(armAngle - 90);
		bulletPoint = CalculateBulletPoint();
	}

	float GetCursorAngle()
	{
		SDL_GetMouseState(&crosshairX, &crosshairY);
		float angle = atan2(armPoint.x - crosshairX, armPoint.y - crosshairY) * (180 / M_PI);
		return angle;
	}

	void TakeDamage(int damage)
	{
		std::cout << "Ouch!" << std::endl;
		hitpoints -= damage;
	}

	void SetFlipH(bool isFlip)
	{
		if (isFlip)
		{
			currentSprite->SetFlipH(true);
			arm->SetFlipV(true);
			arm->SetPosition(currentSprite->Pos().x - currentSprite->Rect().w / 30, currentSprite->Pos().y - 4);
		}
		else
		{
			arm->SetPosition(currentSprite->Pos().x + currentSprite->Rect().w / 3, currentSprite->Pos().y - 4);
			currentSprite->SetFlipH(false);
			arm->SetFlipV(false);
		}
	}
};

