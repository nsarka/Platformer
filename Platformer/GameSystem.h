#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "Textures.h"
#include "LevelManager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


class GameSystem
{
public:
	GameSystem();
	~GameSystem();

	//Keep game loop going
	bool Running() { return bRunning; }

	void HandleEvents();
	void Render();
	void Update();

private:
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	bool bRunning = false;

	LevelManager levelManager;

	//Create player
	GameObject* twoEyes;

};