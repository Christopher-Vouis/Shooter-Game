#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameText.h"
#include "Graphic.h"
#include "Menu.h"
#include "MainGame.h"
#include <iostream>

class Game
{
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Menu* mainMenu;
	bool isRunning;
	SDL_Event event;
	GameMode* currentMode;

public:
	void UpdateScreen();
	void RenderText();
	void RenderGraphics();
	void Cycle();
	bool IsRunning() { return isRunning; }
	Game();
	~Game();
};
