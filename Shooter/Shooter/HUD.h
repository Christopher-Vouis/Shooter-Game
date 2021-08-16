#pragma once
#include "GameText.h"
#include "GameObject.h"

class HUD : public GameObject
{
	GameText scoreLabel;
	int score;
	int hp;

public:
	HUD();
	std::vector<GameText> GetTexts();
	void ChangeScore(int amount);
	void SetScore(int amount);
};

