#include "Enemy.h"
Enemy::Enemy()
{
	//windowSurface = Game::GetWindowSurf();
}

Enemy::~Enemy()
{

}

void Enemy::Cycle()
{
	animation->Cycle();
	currentSprite->SetSurface(animation->GetSurface());
}

void Enemy::MoveObject()
{
	moveProgress += moveSpeed;

	if (moveProgress > 1.0)
	{
		if (direction & directions::UP)
		{
			yMove = -moveProgress;
		}
		else if (direction & directions::DOWN)
		{
			yMove = moveProgress;
		}
		else
		{
			yMove = 0;
		}

		if (direction & directions::LEFT)
		{
			xMove = -moveProgress;
		}
		else if (direction & directions::RIGHT)
		{
			xMove = moveProgress;
		}
		else
		{
			xMove = 0;
		}

		GameObject::MoveObject(xMove, yMove);
		moveProgress -= (int)moveProgress;
		hitBox->Move(xMove, yMove);
	}
}

void Enemy::MoveObject(int x, int y)
{
	GameObject::MoveObject(x, y);
	hitBox->Move(x, y);
}

void Enemy::HandleCollision(GameObject* collision)
{
	if (dynamic_cast<Bullet*>(collision) && hitpoints > 0)
	{
		TakeDamage(1);
	}
}

void Enemy::TakeDamage(int dmg)
{
	hitpoints -= dmg;
	if (hitpoints <= 0)
	{
		Die();
	}
}

void Enemy::Die()
{
	SDL_Event* event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::DESPAWN;
	event->user.data1 = this;
	SDL_PushEvent(event);
	std::cout << "I'm Dead!\n";
}