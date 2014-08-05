#include "GameSystem.h"

//System constructer, init SDL
GameSystem::GameSystem()
{
	log.open("log.txt");

	SDL_Init(SDL_INIT_EVERYTHING);

	pWindow = SDL_CreateWindow("Platformer by Magnolium", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	//Set the default draw color to black
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

	bRunning = true;
}

//System destructor, clean up SDL
GameSystem::~GameSystem()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();

	log.close();
}

void GameSystem::HandleEvents()
{
	SDL_Event Event;

	if (SDL_PollEvent(&Event))
	{
		switch(Event.type)
		{
		case SDL_QUIT:
			bRunning = false;
			break;

		default:
			break;
		}
	}
}

void GameSystem::Render()
{
	SDL_RenderClear(pRenderer);
	SDL_RenderPresent(pRenderer);
}

void GameSystem::Update()
{

}

void GameSystem::Print(std::string Message)
{
	log << "(" << SDL_GetTicks() / 1000 << ") " << Message << "\n";
	std::cout << "(" << SDL_GetTicks() / 1000 << ") " << Message << "\n";
}

void GameSystem::PrintSDLError()
{
	log << "(" << SDL_GetTicks() / 1000 << ") " << "Error: " << std::string(SDL_GetError()) << "\n";
	std::cout << "(" << SDL_GetTicks() / 1000 << ") " << "Error: " << std::string(SDL_GetError()) << "\n";
}