#include "MainGame.h"

MainGame::MainGame()
{
	images.push_back(Graphic());
	images.push_back(Graphic());
	player = new Player(&images.at(1), &images.at(0));
	crosshairSurface = *IMG_Load("img\\crosshair.png");
	crosshair = SDL_CreateColorCursor(&crosshairSurface, 16, 16);

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
}

void MainGame::HandleInputs(SDL_Event e)
{

}

void MainGame::HandleEvents(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEMOTION:
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		player->HandleEvents(e);
		break;
	default:
		break;
	}
}