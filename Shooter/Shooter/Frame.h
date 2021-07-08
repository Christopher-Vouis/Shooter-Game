#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>

class Frame
{
	SDL_Surface img;
	int length = 0;
	std::string pth;

public:
	Frame() {};
	Frame(std::string path, int len)
	{
		pth = path;
		img = *IMG_Load(path.c_str());
		length = len;
	}

	SDL_Surface Surface() { return img; }
	int Length() { return length; }
};

