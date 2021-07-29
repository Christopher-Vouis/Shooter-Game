#pragma once
#include "GameMode.h"
#include "Player.h"
#include "CollisionDetector.h"

class MainGame : public GameMode
{

	Player* player;
	Enemy* enemy;
	bool isPaused;
	SDL_Surface crosshairSurface;
	SDL_Cursor* crosshair;
	int* crosshairX, *crosshairY;
	CollisionDetector collisionDetector = CollisionDetector(renderer);
	SDL_Renderer* renderer;

public:
	MainGame(SDL_Renderer* rend);
	~MainGame();
	void HandleInputs(SDL_Event e);
	void HandleEvents(SDL_Event e);
	void Update();
	void SpawnObject(GameObject* obj);
};

