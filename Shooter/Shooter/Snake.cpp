#include "Snake.h"

Snake::Snake(SDL_Rect bounds)
{
	sprites = std::vector<Graphic>();
	sprites.push_back(Graphic());
	currentSprite = &sprites.at(0);
	*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), 300, 500, 96, 96);	
	std::string walkFrames[2]{ "img\\snake1.png","img\\snake2.png" };
	animation = new Animation(walkFrames, 2, 30);
	direction = ChooseDirection();
	moveSpeed = 1.75;
	hitpoints = 1;
	deathSprite = Graphic(*IMG_Load("img\\snakeDead.png"), 300, 500, 96, 96);
	SDL_Point startPoint = { 0,0 };
	boundary = bounds;

	switch (direction)
	{
	case directions::RIGHT:
		startPoint.x = boundary.x - currentSprite->Rect().w;
		startPoint.y = boundary.y + (rand() % boundary.h);
		*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), startPoint.x, startPoint.y, 96, 96);
		hitBox = new HitBox(static_cast<GameObject*>(this), { currentSprite->Rect().x, currentSprite->Rect().y + 30, 96, 44 });
		break;	
	case directions::LEFT:
		startPoint.x = boundary.w;
		startPoint.y = boundary.y + (rand() % boundary.h);
		*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), startPoint.x, startPoint.y, 96, 96, 0, { 0,0 }, SDL_FLIP_HORIZONTAL);
		hitBox = new HitBox(static_cast<GameObject*>(this), { currentSprite->Rect().x, currentSprite->Rect().y + 30, 96, 44 });
		break;	
	case directions::UP:
		startPoint.x = boundary.x + (rand() % boundary.w);
		startPoint.y = boundary.y + boundary.h;
		*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), startPoint.x, startPoint.y, 96, 96, -90, { 0, 48 });
		hitBox = new HitBox(static_cast<GameObject*>(this), { currentSprite->Rect().x - 18, currentSprite->Rect().y - 48, 44, 96 });
		break;	
	default:
		break;
	}

	SDL_Event* event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::NEW_COLLIDER;
	event->user.data1 = hitBox;
	SDL_PushEvent(event);

}

Snake::~Snake()
{

}

void Snake::Cycle()
{
	if (!isDead)
	{
		MoveObject();
		animation->Cycle();
		currentSprite->SetSurface(animation->GetSurface());

		if (!isReturning)
		{
			switch (direction)
			{
			case directions::RIGHT:
				if (currentSprite->Pos().x + currentSprite->Rect().w > boundary.x + boundary.w)
				{
					*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), currentSprite->Pos().x, currentSprite->Pos().y, 96, 96, 0, { 0,0 }, SDL_FLIP_HORIZONTAL);
					hitBox->SetPosition(currentSprite->Rect().x, currentSprite->Rect().y + 30);
					isReturning = true;
					direction = directions::LEFT;
				}
				break;
			case directions::LEFT:
				if (currentSprite->Pos().x < boundary.x)
				{
					*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), currentSprite->Pos().x, currentSprite->Pos().y, 96, 96);
					//hitBox = new HitBox(static_cast<GameObject*>(this), { currentSprite->Rect().x, currentSprite->Rect().y + 30, 96, 44 });
					isReturning = true;
					direction = directions::RIGHT;
				}
				break;
			case directions::UP:
				if (currentSprite->Pos().y < boundary.y)
				{
					*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), currentSprite->Pos().x, currentSprite->Pos().y, 96, 96, 90, { 0, 48 });
					hitBox->SetPosition(currentSprite->Rect().x - 18, currentSprite->Rect().y + 48);
					isReturning = true;
					direction = directions::DOWN;
				}
				break;
			default:
				break;
			}
		}
	}
	else
	{
		if (flickerTimer < 90)
		{
			float progress = flickerTimer / 15.0;
			if ((progress - (int)progress) == 0)
			{
				if (isFlicker)
				{
					currentSprite->SetFlicker(false);
				}
				else
				{
					currentSprite->SetFlicker(true);
				}

				isFlicker = !isFlicker;
			}
			flickerTimer++;
		}
		else
		{
			event = new SDL_Event();
			event->type = SDL_USEREVENT;
			event->user.code = gameEvents::DESPAWN;
			event->user.data1 = this;
			SDL_PushEvent(event);
			std::cout << "I'm Dead!\n";
		}

	}

}

GameObject::directions Snake::ChooseDirection()
{
	int num = rand() % 15;
	directions result;

	if (num < 5)
	{
		result = directions::RIGHT;
	}
	else if (num < 10)
	{
		result = directions::LEFT;
	}
	else
	{
		result = directions::UP;
	}

	return result;
}

void Snake::Die()
{
	SDL_Event* event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::REMOVE_COLLIDER;
	event->user.data1 = hitBox;
	SDL_PushEvent(event);

	event = new SDL_Event();
	event->type = SDL_USEREVENT;
	event->user.code = gameEvents::SCORE_CHANGE;
	event->user.data1 = &pointValue;
	SDL_PushEvent(event);
	isDead = true;

	if (direction == directions::UP)
	{
		deathSprite.SetPosition(hitBox->GetBox().x - 30, hitBox->GetBox().y);
	}
	else
	{
		deathSprite.SetPosition(currentSprite->Pos().x, currentSprite->Pos().y);
	}

	*currentSprite = deathSprite;
}