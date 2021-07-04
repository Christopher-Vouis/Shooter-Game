#pragma once
#include <SDL.h>
#include "GameText.h"
#include <vector>

class GameMode
{

public:
	virtual void HandleInputs(const Uint8* keystates) {};
	virtual std::vector<GameText> GetTexts() {
		std::vector<GameText> texts;
		return texts;
	};
};

