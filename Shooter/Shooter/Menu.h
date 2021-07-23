#pragma once
#include <SDL_ttf.h>
#include "GameMode.h"
#include "GameText.h"
#include "Graphic.h"

class Menu : public GameMode
{
	std::vector<GameText> texts;
	std::vector<Graphic> images;
	bool isIntro, isQuitSelected;
	const int TITLE = 0, START = 1, QUIT = 2;
	GameObject* cursor;

public:
	Menu();
	~Menu();
	void HandleInputs(SDL_Event e);
	void HandleEvents(SDL_Event e);
	void Update();
	void IntroSequence();
	void SkipIntro();
	std::vector<GameText> GetTexts() { return texts; };
	std::vector<Graphic> GetImages() { return images;};
};

