#include "GameText.h"

GameText::GameText()
{
	_font = TTF_OpenFont(std::string("Fonts/impact.ttf").c_str(), 25);
	_color = { 225, 225, 225 };
	_text = "";
	_rect = { 0,0,0,0 };
}

GameText::GameText(std::string text, SDL_Rect rect, std::string font, SDL_Color color)
{
	_rect = rect;
	_text = text;
	_font = TTF_OpenFont(std::string("Fonts/" + font + ".ttf").c_str(), 25);
	_color = color;
	_surface = *TTF_RenderText_Solid(_font, _text.c_str(), color);
}

GameText::~GameText()
{

}