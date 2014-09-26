#pragma once
#include "SDL.h"
#include "Box2d.h"
#include "SpriteSheet.h"
#include <string>
#include <array>


class Player
{
public:
	Player();
	~Player() {};

	void Update();
	void Draw(SDL_Renderer* pRenderer, bool debug);
	void drawBody(SDL_Renderer* renderer);
	void Load(std::string path, std::string texture, int x, int y, SDL_Renderer* pRenderer, b2World* world);

	void HandleInput();

	int GetWorldPosX() { return playerWorldPos.x; }
	int GetWorldPosY() { return playerWorldPos.y; }

	int GetScreenPosX() { return playerScreenPos.x; }
	int GetScreenPosY() { return playerScreenPos.y; }

	int numFootContacts = 0;

private:
	SpriteSheet* playerSheet = 0;

	SDL_Point playerScreenPos;
	SDL_Point playerWorldPos;

	std::string textureID;
	std::string playerName;

	SDL_Rect objFrame;

	b2BodyDef playerBodyDef;
	b2Body* playerBody;
	b2FixtureDef playerFixtureDef;

	//Is player facing left or right
	bool playerFlip = false;

	//Array so Player::Update() knows which frames are the ones for walking
	std::array<std::string, 11> walkFrames
	{
		{
			"p1_walk01",
			"p1_walk02",
			"p1_walk03",
			"p1_walk04",
			"p1_walk05",
			"p1_walk06",
			"p1_walk07",
			"p1_walk08",
			"p1_walk09",
			"p1_walk10",
			"p1_walk11"
		}
	};
};

