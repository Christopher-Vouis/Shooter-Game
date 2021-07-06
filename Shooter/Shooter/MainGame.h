#pragma once
#include "GameMode.h"
#include "Player.h"

class MainGame : public GameMode
{
	std::vector<GameText> texts;
	std::vector<Graphic> images;
	Player* player;

public:
	MainGame();
	~MainGame();
	void HandleInputs(const Uint8* keystates, bool isRepeat);
	void HandleEvents(SDL_Event e);
	void Update();
	std::vector<GameText> GetTexts() { return texts; };
	std::vector<Graphic> GetImages() { return images; };
};

