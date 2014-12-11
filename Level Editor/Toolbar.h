#pragma once
#include "SDL.h"
#include "Item.h"
#include "Texture.h"
#include <vector>


class Toolbar
{
public:
	Toolbar(int xpos, int ypos, int width, int height);
	~Toolbar();

	void AddItem();
	void RemoveItem();

	void Draw();

private:
	SDL_Rect bounds;
	std::vector<Item*> itemList;
};