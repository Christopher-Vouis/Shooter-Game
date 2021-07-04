#define SDL_MAIN_HANDLED
#pragma once
#include "Game.h"

int main()
{

	Game* game = new Game();

	while (game->IsRunning())
	{
		game->Cycle();
	}

	delete game;

	return 0;
}

