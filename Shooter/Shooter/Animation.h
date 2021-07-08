#pragma once
#include "Frame.h"

class Animation
{
	int frameCount, currentFrame, timer;
	Frame* frames;

public:
	Animation(std::string paths[], int numFrames, int frameLength)
	{
		timer = 0;
		currentFrame = 0;
		frameCount = numFrames;
		Frame* fr = new Frame[numFrames];
		for (int i = 0; i < frameCount; ++i)
		{
			fr[i] = Frame(paths[i], frameLength);
		}
		frames = fr;
	}

	~Animation()
	{
		delete frames;
	}

	void Cycle()
	{
		++timer;
		if (timer >= frames[currentFrame].Length())
		{
			timer = 0;
			++currentFrame;
			if (currentFrame >= frameCount)
			{
				currentFrame = 0;
			}
		}
	}

	Frame GetCurrentFrame()
	{
		return *(frames + currentFrame);
	}

	SDL_Surface GetSurface()
	{
		return (frames + currentFrame)->Surface();
	}
};

