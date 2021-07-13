#include "MainGame.h"

MainGame::MainGame()
{
	images.push_back(Graphic());
	images.push_back(Graphic());
	images.push_back(Graphic());
	player = new Player(&images.at(1), &images.at(0));
	enemy = new Enemy(&images.at(2));
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
	player->Cycle();
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
		if (e.user.code == gameEvents::COLLISION)
		{
			GameObject* obj1 = static_cast<HitBox*>(e.user.data1)->GetObject();
			GameObject* obj2 = static_cast<HitBox*>(e.user.data2)->GetObject();
			obj1->HandleCollision(obj2);
			obj2->HandleCollision(obj1);
		}
	default:
		break;
	}
}