#pragma once
#include "SDL.h"

class Mainmenu
{
public:
	Mainmenu() {};
	~Mainmenu() {};

	void LoadSplash(SDL_Renderer* pRenderer);
	void Draw(SDL_Renderer* pRenderer);
	bool isInMenu = false;

private:

};

