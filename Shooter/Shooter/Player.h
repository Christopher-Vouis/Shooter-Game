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
	Player();
	~Player();
	Graphic GetSprites();
	HitBox* GetHitBox();
	void Cycle();
	void HandleInputs(SDL_Event e);
	void HandleEvents(SDL_Event e);
	void HandleCollision(GameObject* collision);

private:
	void Move();
	SDL_Point CalculateBulletPoint();
	void Shoot();
	void Aim();
	float GetCursorAngle();
	void TakeDamage(int damage);
	void SetFlipH(bool isFlip);
};

