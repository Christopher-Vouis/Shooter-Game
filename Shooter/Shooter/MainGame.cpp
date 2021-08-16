#include "MainGame.h"

MainGame::MainGame(SDL_Renderer* rend, SDL_Surface* surf) : GameMode(rend, surf)
{
	snakeTimer = 0;
	boundary = { 0, 300, 1000, 700 };
	player = new Player(boundary);
	objects.push_back(player);
	crosshairSurface = *IMG_Load("img\\crosshair.png");
	bgSurface = *IMG_Load("img\\background.png");
	crosshair = SDL_CreateColorCursor(&crosshairSurface, 16, 16);
	collisionDetector = CollisionDetector(renderer);
	SDL_SetCursor(crosshair);
	lastTime = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
	thisTime = lastTime;
	srand(time(NULL));
	hud = new HUD();
	texts = hud->GetTexts();
	background = Graphic(bgSurface, 0, 0, surface->w, surface->h);

	for (Graphic img : hud->GetGraphics())
	{
		images.push_back(img);
	}
}

MainGame::~MainGame()
{
	delete player;
	delete crosshair;
	delete crosshairX;
	delete crosshairY;
}

void MainGame::Update()
{
	for (GameObject* obj : objects)
	{
		obj->Cycle();
		if (obj->GetGraphics().size() > 0)
		{
			if (IsOutOfBounds(obj->GetGraphic().Rect()))
			{
				SDL_Event* event = new SDL_Event();
				event->type = SDL_USEREVENT;
				event->user.code = gameEvents::DESPAWN;
				event->user.data1 = obj;
				SDL_PushEvent(event);
			}
		}
	}

	collisionDetector.CheckCollisions();
	thisTime = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);;
	snakeTimer += thisTime - lastTime;
	lastTime = thisTime;

	if (snakeTimer >= 3000)
	{
		SpawnObject(new Snake(boundary));
		snakeTimer = 0;
	}
}

void MainGame::HandleInputs(SDL_Event e)
{

}

void MainGame::HandleEvents(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEMOTION:
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		player->HandleEvents(e);
		break;
	case SDL_USEREVENT:
		switch (e.user.code)
		{
		case gameEvents::NEW_COLLIDER:
		{
			HitBox* toAdd = static_cast<HitBox*>(e.user.data1);
			collisionDetector.AddHitBox(toAdd);
			break;
		}
		case gameEvents::REMOVE_COLLIDER:
		{
			HitBox* toRemove = static_cast<HitBox*>(e.user.data1);
			collisionDetector.RemoveHitBox(toRemove);
			break;
		}
		case gameEvents::DESPAWN:
		{
			GameObject* obj = static_cast<GameObject*>(e.user.data1);
			for (int i = 0; i < objects.size(); ++i)
			{
				if (objects.at(i) == obj)
				{
					delete objects.at(i);
					objects.erase(objects.begin() + i);
					break;
				}
			}
			break;
		}
		case gameEvents::COLLISION:
		{
			HitBox* b1 = static_cast<HitBox*>(e.user.data1);
			HitBox* b2 = static_cast<HitBox*>(e.user.data2);

			GameObject* obj1 = b1->GetObject();
			GameObject* obj2 = b2->GetObject();

			if (std::count(objects.begin(), objects.end(), obj1) &&
				std::count(objects.begin(), objects.end(), obj2))
			{
				obj1->HandleCollision(obj2);
				obj2->HandleCollision(obj1);
			}
			break;
		}
		case gameEvents::SPAWN:
		{
			Bullet* bullet = static_cast<Bullet*>(e.user.data1);
			SpawnObject(bullet);
			break;
		}
		case gameEvents::SCORE_CHANGE:
		{
			hud->ChangeScore(1);
			break;
		}
		default:
			break;
		}
	default:
		break;
	}
}


void MainGame::SpawnObject(GameObject* obj)
{
	objects.push_back(obj);
}

bool MainGame::IsOutOfBounds(SDL_Rect objBox)
{
	if (objBox.x + objBox.w < 0 || objBox.x > surface->w ||
		objBox.y + objBox.h < 0 || objBox.y > surface->h)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<GameText> MainGame::GetTexts()
{
	return hud->GetTexts();
}

Graphic MainGame::GetBackground()
{
	return background;
}