#pragma once
#include "GameMode.h"
#include "Player.h"

class MainGame : public GameMode
{
	std::vector<GameText> texts;
	std::vector<Graphic> images;
	Player* player;
	bool isPaused;
	SDL_Surface crosshairSurface;
	SDL_Cursor* crosshair;
	int* crosshairX, *crosshairY;

public:
	MainGame();
	~MainGame();
	void HandleInputs(SDL_Event e);
	void HandleEvents(SDL_Event e);
	void Update();
	std::vector<GameText> GetTexts() { return texts; };
	std::vector<Graphic> GetImages() { return images; };
};

