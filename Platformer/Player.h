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
	void Freeze();
	void UnFreeze();
	void ToggleNoclip();
	void ToggleFreeze();
	void SetSky(int skyr, int skyg, int skyb, int skya);

	int GetWorldPosX() { return playerWorldPos.x; }
	int GetWorldPosY() { return playerWorldPos.y; }

	int GetScreenPosX() { return playerScreenPos.x; }
	int GetScreenPosY() { return playerScreenPos.y; }

	b2Vec2 GetPlayerVelocity() { return playerBody->GetLinearVelocity(); }

	int numFootContacts = 0;

	//Sky color for debug draw function
	int skyColorR = 0;
	int skyColorG = 0;
	int skyColorB = 0;
	int skyColorA = 0;

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

	int playerDriftCounter = 0;
	const static int playerDriftFrameTotal = 75;
	float32 playerDriftX[playerDriftFrameTotal];
	float32 playerDriftY[playerDriftFrameTotal];
	float32 playerNextToggle = 0.0;

	void CalcAndSetDrift();

	//Is player facing left or right
	bool playerFlip = false;

	//Player noclip
	bool playerNoclip = false;

	//Player freeze
	bool playerFreeze = false;

	//Player duck
	bool playerDuck = false;

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

