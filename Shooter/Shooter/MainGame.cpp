#include "MainGame.h"

MainGame::MainGame()
{
	player = new Player();
	enemy = new Enemy();
	objects.push_back(player);
	objects.push_back(enemy);
	crosshairSurface = *IMG_Load("img\\crosshair.png");
	crosshair = SDL_CreateColorCursor(&crosshairSurface, 16, 16);
	collisionDetector.AddHitBox(player->GetHitBox());
	collisionDetector.AddHitBox(enemy->GetHitBox());
	SDL_SetCursor(crosshair);
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
	}

	collisionDetector.CheckCollisions();
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
		if (e.user.code == gameEvents::NEW_COLLIDER)
		{
			HitBox* toAdd = static_cast<HitBox*>(e.user.data1);
			collisionDetector.AddHitBox(toAdd);
		}
		else if(e.user.code == gameEvents::REMOVE_COLLIDER)
		{
			HitBox* toRemove = static_cast<HitBox*>(e.user.data1);
			collisionDetector.RemoveHitBox(toRemove);
		}
		else if (e.user.code == gameEvents::DESPAWN)
		{
			GameObject* obj = static_cast<GameObject*>(e.user.data1);
			for (int i = 0; i < objects.size(); ++i)
			{
				if (objects.at(i) == obj)
				{
					delete objects.at(i);
					objects.erase(objects.begin() + i);
				}
			}
		}
		else if (e.user.code == gameEvents::COLLISION)
		{
			GameObject* obj1 = static_cast<HitBox*>(e.user.data1)->GetObject();
			GameObject* obj2 = static_cast<HitBox*>(e.user.data2)->GetObject();
			if (obj1 != nullptr && obj2 != nullptr)
			{
				obj1->HandleCollision(obj2);
				obj2->HandleCollision(obj1);
			}

		}
		else if (e.user.code == gameEvents::SPAWN)
		{
			Bullet* bullet = static_cast<Bullet*>(e.user.data1);
			SpawnObject(bullet);
		}
	default:
		break;
	}
}


void MainGame::SpawnObject(GameObject* obj)
{
	objects.push_back(obj);
}