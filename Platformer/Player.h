#pragma once
#include "GameObject.h"
#include "SDL.h"
#include <string>


class Player : public GameObject
{
public:
	Player() {};
	~Player() {};

	void Update();
	void Draw(SDL_Renderer* pRenderer);

private:
	std::string playerName;
};

