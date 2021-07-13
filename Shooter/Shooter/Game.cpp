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
		if (images.at(i).Rotation() == 0)
		{
			SDL_RenderCopy(renderer, texture, NULL, &images.at(i).Rect());
		}
		else
		{
			SDL_RenderCopyEx(renderer, texture, NULL, &images.at(i).Rect(), images.at(i).Rotation(), &images.at(i).Origin(), SDL_FLIP_NONE);
		}

		SDL_DestroyTexture(texture);
	}
}

void Game::Cycle()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
		else if (event.type == SDL_USEREVENT)
		{
			switch (event.user.code)
			{
			case gameEvents::START:
				delete currentMode;
				currentMode = new MainGame();
				break;
			case gameEvents::COLLISION:
				currentMode->HandleEvents(event);
				break;
			default:
				break;
			}
		}
		else
		{
			currentMode->HandleEvents(event);
		}
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