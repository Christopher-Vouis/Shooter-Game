#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameMode.h"
#include <iostream>
#include "GameText.h"

class Menu : public GameMode
{
	GameText* title, *prompts;
	std::vector<GameText> texts;

public:
	Menu();
	~Menu();
	void HandleInputs(const Uint8* keystates);
	std::vector<GameText> GetTexts();
};

