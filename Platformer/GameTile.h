#pragma once
#include <string>
#include <iostream>
#include "SDL.h"
#include "Textures.h"

class GameTile
{
public:
	GameTile();
	~GameTile();

	void Draw(SDL_Renderer* pRenderer);

	//Set tile properties
	void SetFrame(SDL_Rect Frame);
	void SetImageName(std::string ImageName);
	void SetTileName(std::string TileName);
	void SetPoint(SDL_Point Point);
	void SetPhysics(int Physics);
	void SetSound(int Sound);
	void SetAction(bool Action);

	//Get tile properties
	int GetPhysics() { return physics; }
	int GetSound() { return sound; }
	std::string GetImageName() { return ImageName; }
	std::string GetTileName() { return TileName; }

	//Is this tile in screen
	bool IsTileInScreen(int x, int y, int w, int h);

private:
	SDL_Rect frame;
	std::string ImageName;
	std::string TileName;
	SDL_Point point;
	int physics;	//will use an enumerator
	int sound;		//will use an enumerator
	bool action;
};

