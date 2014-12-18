#pragma once
#include "SDL.h"
#include <string>

class Item
{
public:
	//Size and location on the toolbar
	Item(int xpos, int ypos, int width, int height);
	~Item();

	void DrawOnScene();
	void DrawOnToolbar();

private:
	SDL_Rect spriteSheetFrame;
	SDL_Rect toolbarBounds;
	std::string name;
};

