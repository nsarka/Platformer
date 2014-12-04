#pragma once
#include "SDL.h"

class Item
{
public:
	Item(int xpos, int ypos, int width, int height);
	~Item();

private:
	SDL_Rect bounds;
};

