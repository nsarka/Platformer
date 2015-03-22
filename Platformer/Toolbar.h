/*
	Work in progress. Will finish levelmanager.save first
	so editing the level with toolbar has a purpose
*/

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

