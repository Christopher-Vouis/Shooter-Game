#include "MainGame.h"

MainGame::MainGame()
{
	images.push_back(Graphic());
	player = new Player(&images.at(0));
}

MainGame::~MainGame()
{

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
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		player->HandleEvents(e);
		break;
	default:
		break;
	}
}