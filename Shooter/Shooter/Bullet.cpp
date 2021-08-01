#include "Bullet.h"

Bullet::Bullet(SDL_Point point, int angle)
{
	float radians = angle * (M_PI / 180);
	position = point;
	sprites.push_back(Graphic(*IMG_Load("img//cowboy//shot.png"), point.x, point.y, 16, 2, angle, { 8,1 }));
	currentSprite = &sprites.at(0);
	vectorX = cos(radians);
	vectorY = sin(radians);
	ArrangeHitBoxes(angle);
};

Bullet::~Bullet()
{
	SDL_Event* event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::REMOVE_COLLIDER;
	event->user.data1 = &hitBox1;
	SDL_PushEvent(event);

	event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::REMOVE_COLLIDER;
	event->user.data1 = &hitBox2;
	SDL_PushEvent(event);
}

void Bullet::Cycle()
{
	Move();
}

void Bullet::Move()
{
	moveProgressX += moveSpeed * vectorX;
	moveProgressY += moveSpeed * vectorY;

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
		hitBox1.Move(step.x, step.y);
		hitBox2.Move(step.x, step.y);
		step = { 0, 0 };
	}
}

void Bullet::ArrangeHitBoxes(int angle)
{
	SDL_Rect* re = new SDL_Rect({ 100,100, 10, 10 });
	const SDL_Rect* r = re;

	if ((angle < 0 && angle >= -30) || (angle > 0 && angle <= 30))
	{
		//horizontal left to right
		*re = { position.x,position.y - 4 , 9, 9 };
		hitBox1 = HitBox(this, *re);
		*re = { position.x + 9, position.y - 4 , 9, 9 };
		hitBox2 = HitBox(this, *re);
	}
	else if ((angle < -30 && angle >= -60))
	{
		//diagonal up left to right
		*re = { position.x,position.y, 9, 9 };
		hitBox1 = HitBox(this, *re);
		*re = { position.x + 9, position.y - 9 , 9, 9 };
		hitBox2 = HitBox(this, *re);
	}
	else if ((angle < -60 && angle >= -120))
	{
		//vertical bottom to top
		*re = { position.x + 4, position.y - 8 , 9, 9 };
		hitBox1 = HitBox(this, *re);
		*re = { position.x + 4, position.y + 1 , 9, 9 };
		hitBox2 = HitBox(this, *re);
	}
	else if ((angle < -120 && angle >= -150))
	{
		//diagonal up right to left
		*re = { position.x + 9,position.y, 9, 9 };
		hitBox1 = HitBox(this, *re);
		*re = { position.x, position.y - 9, 9, 9 };
		hitBox2 = HitBox(this, *re);
	}
	else if ((angle < -150 && angle >= -210))
	{
		//horizontal right to left
		*re = { position.x,position.y - 4 , 9, 9 };
		hitBox1 = HitBox(this, *re);
		*re = { position.x + 9, position.y - 4 , 9, 9 };
		hitBox2 = HitBox(this, *re);
	}
	else if ((angle < -210 && angle >= -240))
	{
		//diagonal down right to left
		*re = { position.x + 9, position.y-9, 9, 9 };
		hitBox1 = HitBox(this, *re);
		*re = { position.x, position.y , 9, 9 };
		hitBox2 = HitBox(this, *re);
	}
	else if ((angle < -210 && angle >= -65) || (angle > 30 && angle < 60))
	{
		//vertical down
		*re = { position.x, position.y - 9, 9, 9 };
		hitBox1 = HitBox(this, *re);
		*re = { position.x + 9, position.y , 9, 9 };
		hitBox2 = HitBox(this, *re);
	}
	else if ((angle > 60) || (angle < -240))
	{
		*re = { position.x + 4, position.y - 8 , 9, 9 };
		hitBox1 = HitBox(this, *re);
		*re = { position.x + 4, position.y + 1 , 9, 9 };
		hitBox2 = HitBox(this, *re);
	}

	SDL_Event* event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::NEW_COLLIDER;
	event->user.data1 = &hitBox1;
	SDL_PushEvent(event);

	event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::NEW_COLLIDER;
	event->user.data1 = &hitBox2;
	SDL_PushEvent(event);
}