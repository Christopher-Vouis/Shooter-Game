#include "HUD.h"

HUD::HUD()
{
	score = 0;
	scoreLabel = GameText("SCORE : " + std::to_string(score), { 25 , 25, 300,100 }, "impact", { 225, 0, 0 });
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