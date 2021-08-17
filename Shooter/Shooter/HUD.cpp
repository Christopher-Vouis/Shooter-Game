#include "HUD.h"

HUD::HUD()
{
	score = 0;
	scoreLabel = GameText("SCORE : " + std::to_string(score), { 25 , 25, 300,100 }, "impact", { 225, 0, 0 });
	sprites.push_back(Graphic(*IMG_Load("img\\heart.png"), 600, 25, 96, 96));
	sprites.push_back(Graphic(*IMG_Load("img\\heart.png"), 725, 25, 96, 96));
	sprites.push_back(Graphic(*IMG_Load("img\\heart.png"), 850, 25, 96, 96));
}

std::vector<GameText> HUD::GetTexts()
{
	return { scoreLabel };
}

void HUD::ChangeScore(int amount)
{
	score += amount;
	scoreLabel = GameText("SCORE : " + std::to_string(score), { 25 , 25, 300,100 }, "impact", { 225, 0, 0 });
}

void HUD::SetScore(int amount)
{
	score = amount;
	scoreLabel = GameText("SCORE : " + std::to_string(score), { 25 , 25, 300,100 }, "impact", { 225, 0, 0 });
}

void HUD::HideHearts(int amount)
{
	for (int i = amount; i > 0; --i)
	{
		if (sprites.size() >= i)
		{
			sprites.pop_back();
		}
	}
}

void HUD::AddHearts(int amount)
{
	for (int i = 0; i < amount; ++i)
	{
		if (sprites.size() < 3)
		{
			sprites.pop_back();
		}
	}
}