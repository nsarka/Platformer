#pragma once
#include "GameObject.h"
#include "SpriteSheet.h"
#include "SDL.h"
#include <string>
#include <array>


class Player : public GameObject
{
public:
	Player();
	~Player() {};

	void Update();
	void Draw(SDL_Renderer* pRenderer);

private:
	SpriteSheet* playerSheet = 0;
	std::string playerName;
	bool flip = false;

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

