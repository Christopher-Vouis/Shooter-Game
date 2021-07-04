#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameMode.h"
#include <iostream>
#include "GameText.h"

class Menu : public GameMode
{
	std::vector<GameText> texts;
	bool isIntro;
	const int TITLE = 0, START = 1, QUIT = 2;

public:
	Menu();
	~Menu();
	void HandleInputs(const Uint8* keystates);
	void Update();
	void IntroSequence();
	std::vector<GameText> GetTexts();
};

