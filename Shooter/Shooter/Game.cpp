#include "Game.h"
#include <string>

void Game::UpdateScreen()
{
	RenderGraphic(currentMode->GetBackground());
	RenderText();

	for (Graphic img : currentMode->GetImages())
	{
		RenderGraphic(img);
	}
	
	for (GameObject* obj : currentMode->GetObjects())
	{
		for (Graphic graphic : obj->GetGraphics())
		{
			RenderGraphic(graphic);
		}
	}

	SDL_RenderPresent(renderer);
	SDL_FreeSurface(surface);
	SDL_RenderClear(renderer);
	SDL_DestroyTexture(texture);
};

void Game::RenderText()
{
	std::vector<GameText> texts = currentMode->GetTexts();
	SDL_Surface surf;
	SDL_Rect rect;
	for (int i = 0; i < texts.size(); ++i)
	{
		surf = texts.at(i).Surface();
		rect = texts.at(i).Rect();
		texture = SDL_CreateTextureFromSurface(renderer, &surf);
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
	}
}

void Game::RenderGraphic(Graphic graphic)
{
	SDL_Surface surf = graphic.Surface();
	SDL_Rect rect = graphic.Rect();
	SDL_Point point = graphic.Origin();
	texture = SDL_CreateTextureFromSurface(renderer, &surf);
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, graphic.Rotation(), &point, graphic.FlipMode());
	SDL_DestroyTexture(texture);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
				currentMode = new MainGame(renderer, surface);
				break;	
			case gameEvents::MENU:
				delete currentMode;
				currentMode = new Menu(renderer, surface);
			default:
				currentMode->HandleEvents(event);
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
	currentMode = new Menu(renderer, surface);
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