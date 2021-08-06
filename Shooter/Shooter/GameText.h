#pragma once
#include <SDL_ttf.h>
#include <string>
#include "Graphic.h"

class GameText : public Graphic

{
	std::string _text;
	TTF_Font* _font;
	SDL_Color _color;

public:
	GameText();
	GameText(std::string text, SDL_Rect rect, std::string font, SDL_Color color);
	~GameText();
	std::string Text() { return _text; }
};
