#include "Bullet.h"

Bullet::Bullet(SDL_Point point, int angle)
{
	windowSurf = Game::GetWindowSurf();
	float radians = angle * (M_PI / 180);
	position = point;
	sprites.push_back(Graphic(*IMG_Load("img//cowboy//shot.png"), point.x, point.y, 16, 2, angle, { 8,1 }));
	currentSprite = &sprites.at(0);
	vectorX = cos(radians);
	vectorY = sin(radians);
	
	std::cout << angle << std::endl;
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
	if ((angle < 0 && angle >= -30) || (angle > 0 && angle <= 30))
	{
		//horizontal left to right
		hitBox1 = HitBox(this, { position.x - 1, position.y - 1, 9, 4 });
		hitBox2 = HitBox(this, { position.x + 1 + currentSprite->Rect().w / 2, position.y - 1, 9, 4 });
	}
	else if ((angle < -30 && angle >= -60))
	{
		//diagonal up left to right
		hitBox1 = HitBox(this, { position.x - 1, position.y - 1, 9, 4 });
		hitBox2 = HitBox(this, { position.x + 1 + currentSprite->Rect().w / 2, position.y - 1, 9, 4 });
	}
	else if ((angle < -60 && angle >= -120))
	{
		//vertical bottom to top
		hitBox1 = HitBox(this, { position.x - 1, position.y - 1, 9, 4 });
		hitBox2 = HitBox(this, { position.x + 1 + currentSprite->Rect().w / 2, position.y - 1, 9, 4 });
	}
	else if ((angle < -120 && angle >= -150))
	{
		//diagonal up right to left
		hitBox1 = HitBox(this, { position.x - 1, position.y - 1, 9, 4 });
		hitBox2 = HitBox(this, { position.x + 1 + currentSprite->Rect().w / 2, position.y - 1, 9, 4 });
	}
	else if ((angle < -150 && angle >= -210))
	{
		//horizontal right to left
		hitBox1 = HitBox(this, { position.x - 1, position.y - 1, 9, 4 });
		hitBox2 = HitBox(this, { position.x + 1 + currentSprite->Rect().w / 2, position.y - 1, 9, 4 });
	}
	else if ((angle < -210 && angle >= -240))
	{
		//diagonal down right to left
		hitBox1 = HitBox(this, { position.x - 1, position.y - 1, 9, 4 });
		hitBox2 = HitBox(this, { position.x + 1 + currentSprite->Rect().w / 2, position.y - 1, 9, 4 });
	}
	else if ((angle < -210 && angle >= -65) || (angle > 30 && angle < 60))
	{
		//vertical down
		hitBox1 = HitBox(this, { position.x - 1, position.y - 1, 9, 4 });
		hitBox2 = HitBox(this, { position.x + 1 + currentSprite->Rect().w / 2, position.y - 1, 9, 4 });
	}
	else if ((angle > 60))
	{
		//diag down right
		hitBox1 = HitBox(this, { position.x - 1, position.y - 1, 9, 4 });
		hitBox2 = HitBox(this, { position.x + 1 + currentSprite->Rect().w / 2, position.y - 1, 9, 4 });
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