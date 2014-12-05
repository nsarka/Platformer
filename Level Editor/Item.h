#pragma once
#include "SDL.h"

class Item
{
public:
	//Size and location on the toolbar
	Item(int xpos, int ypos, int width, int height);
	~Item();

private:
	SDL_Rect bounds;
};

