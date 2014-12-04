#pragma once
#include "SDL.h"
#include "Item.h"
#include <vector>


class Toolbar
{
public:
	Toolbar(int xpos, int ypos, int width, int height);
	~Toolbar();

	void AddItem();
	void RemoveItem();

private:
	SDL_Rect bounds;
	std::vector<Item*> itemList;
};