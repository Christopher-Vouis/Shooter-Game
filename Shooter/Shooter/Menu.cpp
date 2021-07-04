#include "Menu.h"

Menu::Menu()
{
	title = new GameText("SHOOTER", { 300, 100, 400, 100 }, "impact", { 225, 0, 0 });
	prompts = new GameText("Press Enter", { 300, 500, 200, 75 }, "impact", { 225, 225, 225 });
	texts.push_back(*title);
	texts.push_back(*prompts);
}

Menu::~Menu()
{

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