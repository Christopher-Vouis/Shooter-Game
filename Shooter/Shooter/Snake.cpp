#include "Snake.h"

Snake::Snake(int screenWidth, int screenHeight)
{
	sprites = std::vector<Graphic>();
	sprites.push_back(Graphic());
	currentSprite = &sprites.at(0);
	*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), 300, 500, 96, 96);	
	std::string walkFrames[2]{ "img\\snake1.png","img\\snake2.png" };
	animation = new Animation(walkFrames, 2, 30);
	direction = ChooseDirection();
	moveSpeed = 1.25;
	hitpoints = 1;

	SDL_Point startPoint = { 0,0 };

	switch (direction)
	{
	case directions::RIGHT:
		startPoint.x = -currentSprite->Rect().w;
		startPoint.y = rand() % screenHeight;
		*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), startPoint.x, startPoint.y, 96, 96);
		hitBox = new HitBox(static_cast<GameObject*>(this), { currentSprite->Rect().x, currentSprite->Rect().y + 30, 96, 44 });
		break;	
	case directions::LEFT:
		startPoint.x = screenWidth;
		startPoint.y = rand() % screenHeight;
		*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), startPoint.x, startPoint.y, 96, 96, 0, { 0,0 }, SDL_FLIP_HORIZONTAL);
		hitBox = new HitBox(static_cast<GameObject*>(this), { currentSprite->Rect().x, currentSprite->Rect().y + 30, 96, 44 });
		break;	
	case directions::UP:
		startPoint.x = rand() % screenWidth;
		startPoint.y = screenHeight;
		*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), startPoint.x, startPoint.y, 96, 96, -90, { 0, 48 });
		hitBox = new HitBox(static_cast<GameObject*>(this), { currentSprite->Rect().x - 18, currentSprite->Rect().y - 48, 44, 96 });
		break;	
	case directions::DOWN:
		startPoint.x = rand() % screenWidth;
		startPoint.y = -currentSprite->Rect().w;
		*currentSprite = Graphic(*IMG_Load("img\\snake1.png"), startPoint.x, startPoint.y, 96, 96, 90, { 0, 48 });
		hitBox = new HitBox(static_cast<GameObject*>(this), { currentSprite->Rect().x - 26, currentSprite->Rect().y + 48, 44, 96 });
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
	MoveObject();
	animation->Cycle();
	currentSprite->SetSurface(animation->GetSurface());
}

GameObject::directions Snake::ChooseDirection()
{
	int num = rand() % 20;
	directions result;

	if (num < 5)
	{
		result = directions::RIGHT;
	}
	else if (num < 10)
	{
		result = directions::LEFT;
	}
	else if (num < 15)
	{
		result = directions::UP;
	}
	else
	{
		result = directions::DOWN;
	}

	return result;
}

