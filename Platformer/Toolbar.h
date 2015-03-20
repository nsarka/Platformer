#pragma once
#include "SpriteSheet.h"
#include "Textures.h"

class Toolbar
{
public:
	Toolbar(SpriteSheet* levelSheet);
	~Toolbar() {};

	void Populate();
	void Draw(SDL_Renderer* pRenderer);

private:
	SDL_Rect editorBounds;
};

