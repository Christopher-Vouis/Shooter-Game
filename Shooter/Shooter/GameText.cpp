#include "GameText.h"

GameText::GameText(std::string text, SDL_Rect rect, std::string font, SDL_Color color)
{
	_text = text;
	_rect = rect;
	_font = TTF_OpenFont(std::string("Fonts/" + font + ".ttf").c_str(), 25);
	_color = color;
	_surface = TTF_RenderText_Solid(_font, _text.c_str(), color);
}

GameText::~GameText()
{

}

//Getters
SDL_Surface* GameText::Surface()
{
	return _surface;
}

SDL_Rect* GameText::Rect()
{
	return &_rect;
}