#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "Textures.h"
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

	//Print error to log (and console in debug mode)
	void Print(std::string Message);
	void PrintSDLError();

private:
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	bool bRunning = false;

	std::vector<GameObject*> gameObjects;
	std::ofstream log;

	//Test, draw Twoeyes
	GameObject* twoEyes;
};