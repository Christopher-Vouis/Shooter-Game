#include "Menu.h"

Menu::Menu()
{
	isIntro = true;
	texts.push_back(GameText("SHOOTER", { 300, 100, 400, 100 }, "impact", { 225, 0, 0 }));
	texts.push_back(GameText("Start", { 300, 500, 200, 75 }, "impact", { 225, 225, 225 }));
	texts.push_back(GameText("Quit", { 300, 700, 200, 75 }, "impact", { 225, 225, 225 }));
}

Menu::~Menu()
{

}

void Menu::Update()
{
	if (isIntro)
	{
		IntroSequence();
	}
}

void Menu::IntroSequence()
{
	texts.at(TITLE).Rect()->y += 1;
}

void Menu::HandleInputs(const Uint8* keystates) {
	if (keystates[SDL_SCANCODE_RETURN])
	{
		std::cout << "Enter";
	}
}

std::vector<GameText> Menu::GetTexts()
{
	return texts;
}