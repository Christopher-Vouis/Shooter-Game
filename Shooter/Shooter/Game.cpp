#include "Game.h"

void Game::UpdateScreen()
{
	SDL_FreeSurface(surface);
	SDL_RenderClear(renderer);
	SDL_DestroyTexture(texture);
	RenderText();
	RenderGraphics();
	SDL_RenderPresent(renderer);
};

void Game::RenderText()
{
	std::vector<GameText> texts = currentMode->GetTexts();
	for (int i = 0; i < texts.size(); ++i)
	{
		texture = SDL_CreateTextureFromSurface(renderer, &texts.at(i).Surface());
		SDL_RenderCopy(renderer, texture, NULL, &texts.at(i).Rect());
		SDL_DestroyTexture(texture);
	}
}

void Game::RenderGraphics()
{
	std::vector<Graphic> images = currentMode->GetImages();
	for (int i = 0; i < images.size(); ++i)
	{
		texture = SDL_CreateTextureFromSurface(renderer, &images.at(i).Surface());
		SDL_RenderCopy(renderer, texture, NULL, &images.at(i).Rect());
		SDL_DestroyTexture(texture);
	}
}

void Game::Cycle()
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
		currentMode->HandleEvents(event);
	}

	currentMode->Update();

	SDL_Delay(16);
	UpdateScreen();
}

Game::Game()
{
	SDL_SetMainReady();
	TTF_Init();
	isRunning = true;
	window = SDL_CreateWindow("Shooter", 750, 250, 1000, 1000, 0);
	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, 0);
	currentMode = new Menu();
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(window);
}

Game::~Game()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}