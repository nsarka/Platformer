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

	static void PrintSDLError();
	static void Print(std::string message);
	static void Print(int message);

private:
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	bool bRunning = false;

	std::vector<GameObject*> levelObjects;
	std::vector<GameObject*> backgroundObjects;

	//Test, draw Twoeyes
	GameObject* twoEyes;
};