#include "MainGame.h"

MainGame::MainGame()
{
	player = new Player();
	images.push_back(player->GetSprites().at(0));
}

MainGame::~MainGame()
{

}

void MainGame::Update()
{

}

void MainGame::HandleInputs(const Uint8* keystates, bool isRepeat)
{

}

void MainGame::HandleEvents(SDL_Event e)
{
	switch (e.type)
	{

	}
}