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

