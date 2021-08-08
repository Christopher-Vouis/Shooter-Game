#include "Menu.h"

Menu::Menu(SDL_Renderer* rend, SDL_Surface* surf) : GameMode(rend, surf)
{
	isIntro = true;
	texts.push_back(GameText("SHOOTER", { 300, 0, 400, 100 }, "impact", { 225, 0, 0 }));
	texts.push_back(GameText("Start", { -200, 600, 200, 75 }, "impact", { 225, 225, 225 }));
	texts.push_back(GameText("Quit", { 1000, 700, 200, 75 }, "impact", { 225, 225, 225 }));
	cursor = new GameObject(Graphic(*IMG_Load("img\\Cursor.jpg"), -500, 600, 75, 75));
	objects.push_back(cursor);
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
	if (texts.at(TITLE).Pos().y < 300)
	{
		texts.at(TITLE).Move(0,5);
	}
	else if (texts.at(START).Rect().x < 400)
	{
		texts.at(START).Move(10, 0);
		texts.at(QUIT).Move(-10, 0);
	}
	else
	{
		cursor->SetPosition(310, (isQuitSelected ? texts.at(QUIT).Pos().y : texts.at(START).Pos().y));
		isIntro = false;
	}
}

void Menu::HandleInputs(SDL_Event e) 
{
		if (e.key.keysym.scancode == SDL_SCANCODE_RETURN)
		{
			if (isQuitSelected)
			{
				SDL_Event quit;
				quit.type = SDL_QUIT;
				SDL_PushEvent(&quit);
			}
			else
			{
				SDL_Event start;
				start.type = SDL_USEREVENT;
				start.user.code = gameEvents::START;
				SDL_PushEvent(&start);
			}
		}
		else if (!e.key.repeat && (e.key.keysym.scancode == SDL_SCANCODE_W || e.key.keysym.scancode == SDL_SCANCODE_UP
			|| e.key.keysym.scancode == SDL_SCANCODE_S || e.key.keysym.scancode == SDL_SCANCODE_DOWN))
		{
			isQuitSelected = !isQuitSelected;
			cursor->SetPosition(310, (isQuitSelected ? texts.at(QUIT).Pos().y : texts.at(START).Pos().y));
		}
}

void Menu::HandleEvents(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (isIntro)
		{
			SkipIntro();
		}
		else
		{
			HandleInputs(e);
		}
		break;
	default:
		break;
	}
}

void Menu::SkipIntro()
{
	texts.at(TITLE).SetPosition(300, 300);
	texts.at(START).SetPosition(400, 600);
	texts.at(QUIT).SetPosition(400, 700);
	isIntro = false;
	cursor->SetPosition(310, (isQuitSelected ? texts.at(QUIT).Pos().y : texts.at(START).Pos().y));
}