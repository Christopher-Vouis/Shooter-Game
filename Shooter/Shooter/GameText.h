#pragma once
#include <SDL_ttf.h>
#include <string>

class GameText

{
	std::string _text;
	SDL_Rect _rect;
	TTF_Font* _font;
	SDL_Color _color;
	SDL_Surface* _surface;

public:
	GameText(std::string text, SDL_Rect rect, std::string font, SDL_Color color);
	~GameText();

	//Getters
	SDL_Surface* Surface();
	SDL_Rect* Rect();
	std::string Text() { return _text; }
};
