#pragma once
#include "SDL.h"
#include "SpriteSheet.h"
#include <string>
#include <array>


class Player
{
public:
	Player();
	~Player() {};

	void Update();
	void Draw(SDL_Renderer* pRenderer);
	void Load(std::string path, std::string texture, int x, int y, SDL_Renderer* pRenderer);

	void HandleInput();

	int GetWorldPosX() { return playerWorldPos.x; }
	int GetWorldPosY() { return playerWorldPos.y; }

	int GetScreenPosX() { return playerScreenPos.x; }
	int GetScreenPosY() { return playerScreenPos.y; }

private:
	SpriteSheet* playerSheet = 0;

	SDL_Point playerScreenPos;
	SDL_Point playerWorldPos;

	std::string textureID;
	std::string playerName;

	SDL_Rect objFrame;

	//Is player facing left or right
	bool playerFlip = false;

	//Array so Player::Update() knows which frames are the ones for walking
	std::array<std::string, 11> walkFrames
	{
		{
			"p2_walk01",
			"p2_walk02",
			"p2_walk03",
			"p2_walk04",
			"p2_walk05",
			"p2_walk06",
			"p2_walk07",
			"p2_walk08",
			"p2_walk09",
			"p2_walk10",
			"p2_walk11"
		}
	};
};

