#pragma once
#include <string>
#include "SDL.h"
#include "Textures.h"

class GameTile
{
public:
	GameTile();
	~GameTile();

	void Draw(SDL_Renderer* pRenderer);

	SDL_Rect frame;
	std::string textureName;
	SDL_Point point;
	bool physics;
	int sound; //will use an enumerator
	bool action;
};

