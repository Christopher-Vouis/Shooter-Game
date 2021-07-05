#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameText.h"
#include "Graphic.h"
#include <vector>

class GameMode
{

public:
	std::vector<Graphic>::iterator targetGraphic;

	virtual void HandleInputs(const Uint8* keystates, bool isRepeat) {};
	virtual void HandleEvents(SDL_Event e) {};
	virtual void Update() {};
	virtual std::vector<GameText> GetTexts() {
		std::vector<GameText> texts;
		return texts;
	};
	virtual  std::vector<Graphic> GetImages() {
		std::vector<Graphic> surfs;
		return surfs;
	};
};

