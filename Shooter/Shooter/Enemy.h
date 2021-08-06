#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include <chrono>

class Enemy : public GameObject
{
protected:
	Animation* animation;
	double moveSpeed = 0.75;
	double moveProgress = 0.0;
	int xMove, yMove;
	int hitpoints;
	int pointValue;
	directions direction;
	SDL_Surface windowSurface;

public:
	Enemy();
	~Enemy();
	virtual void Cycle();
	virtual void MoveObject();
	virtual void MoveObject(int x, int y);
	virtual void HandleCollision(GameObject* collision);
	virtual void TakeDamage(int dmg);
	virtual void Die();
};

