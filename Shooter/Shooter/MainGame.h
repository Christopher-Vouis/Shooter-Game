#pragma once
#include "Snake.h"
#include "GameMode.h"
#include "Player.h"
#include "CollisionDetector.h"
#include <chrono>
#include "HUD.h"

class MainGame : public GameMode
{
	Player* player;
	GameObject* enemy;
	HUD* hud;
	bool isPaused;
	SDL_Surface crosshairSurface, bgSurface;
	SDL_Cursor* crosshair;
	int* crosshairX, *crosshairY;
	CollisionDetector collisionDetector = CollisionDetector(renderer);
	int snakeTimer, lastTime, thisTime;
	Graphic background;

public:
	MainGame(SDL_Renderer* rend, SDL_Surface* surf);
	~MainGame();
	void HandleInputs(SDL_Event e);
	void HandleEvents(SDL_Event e);
	void Update();
	void SpawnObject(GameObject* obj);
	bool IsOutOfBounds(SDL_Rect objBox);
	std::vector<GameText> GetTexts();
	Graphic GetBackground();
};

