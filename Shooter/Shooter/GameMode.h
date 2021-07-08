#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameText.h"
#include "Graphic.h"
#include <vector>

#ifndef GAMEMODE_H
	enum gameEvents { START, PAUSE, MENU, QUIT };
#endif

class GameMode
{

public:
	virtual void HandleInputs(SDL_Event e) {};
	virtual void HandleEvents(SDL_Event e) {};
	virtual void Update() {};
	virtual std::vector<GameText> GetTexts() {
		std::vector<GameText> texts;
		return texts;
	};
	virtual  std::vector<Graphic> GetImages() {
		std::vector<Graphic> imgs;
		return imgs;
	};
};

