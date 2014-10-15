#pragma once
#include <string>
#include <iostream>
#include "SDL.h"
#include "Textures.h"
#include "Box2d.h"

class GameTile
{
public:
	GameTile();
	~GameTile();

	void Draw(SDL_Renderer* pRenderer, bool tileDebug);
	void Update();
	void drawBody(SDL_Renderer* renderer);

	//Set tile properties
	void SetFrame(SDL_Rect Frame);
	void SetImageName(std::string ImageName);
	void SetTileName(std::string TileName);
	void SetPoint(SDL_Point Point);
	b2Body* SetPhysics(int Physics, b2World* world);
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
	float angle;	//Stored in degrees, convert to rads when needed

	b2BodyDef tileBodyDef;
	b2Body* tileBody = 0;
	b2FixtureDef tileFixtureDef;
};

