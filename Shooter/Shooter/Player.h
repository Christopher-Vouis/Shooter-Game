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
#include "Boundary.h"

class Player : public GameObject
{
	SDL_Surface idleSurface, armSurface;
	Animation* walkAnim;
	Graphic* arm;

	int hitpoints = 3, xMove, yMove, crosshairX, crosshairY, armAngle, damage;
	bool invincible = false, isDamaged = false;
	double moveSpeed = 1.25;
	double moveProgress = 0.0;
	const Uint8* keyboardState;
	SDL_Point armPoint, bulletPoint, lastPos, lastMove;

	enum class playerState
	{
		IDLE,
		WALKING,
		DEAD
	};

	playerState state;
	uint8_t movementDir;

public:
	Player(SDL_Rect bounds);
	~Player();
	Graphic GetSprites();
	void Cycle();
	void HandleInputs(SDL_Event e);
	void HandleEvents(SDL_Event e);
	void HandleCollision(GameObject* collision);
	void SetPosition(int x, int y);
	SDL_Rect bound;

private:
	void Move();
	SDL_Point CalculateBulletPoint();
	void Shoot();
	void Aim();
	float GetCursorAngle();
	void TakeDamage(int damage);
	void SetFlipH(bool isFlip);
};

