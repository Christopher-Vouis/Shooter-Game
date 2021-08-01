#pragma once
#include "Snake.h"
#include "GameMode.h"
#include "Player.h"
#include "CollisionDetector.h"
#include <chrono>
class MainGame : public GameMode
{
	Player* player;
	GameObject* enemy;
	bool isPaused;
	SDL_Surface crosshairSurface;
	SDL_Cursor* crosshair;
	int* crosshairX, *crosshairY;
	CollisionDetector collisionDetector = CollisionDetector(renderer);
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	int snakeTimer, lastTime, thisTime;

public:
	MainGame(SDL_Renderer* rend, SDL_Surface* surf);
	~MainGame();
	void HandleInputs(SDL_Event e);
	void HandleEvents(SDL_Event e);
	void Update();
	void SpawnObject(GameObject* obj);
	bool IsOutOfBounds(SDL_Rect objBox);
};

