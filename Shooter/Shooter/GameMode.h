#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameText.h"
#include "Graphic.h"
#include <vector>
#include "GameEvents.h"
#include "GameObject.h"

class GameMode
{

protected:
	std::vector<GameObject*> objects;
	std::vector<GameText> texts;
	std::vector<Graphic> images;

public:
	virtual void HandleInputs(SDL_Event e) {};
	virtual void HandleEvents(SDL_Event e) {};
	virtual void Update() {};
	virtual std::vector<GameObject*> GetObjects() {

		return objects;
	};
	virtual std::vector<GameText> GetTexts() {

		return texts;
	};
	virtual  std::vector<Graphic> GetImages() {

		return images;
	};
};

