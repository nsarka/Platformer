#ifndef __GameSystem__
#define __GameSystem__

#include "SDL.h"
#include <fstream>
#include <iostream>
#include <string>

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

	//Print to log (and console in debug mode)
	void Print(std::string Message);
	void PrintSDLError();

private:
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	bool bRunning = false;

	std::ofstream log;
};


#endif