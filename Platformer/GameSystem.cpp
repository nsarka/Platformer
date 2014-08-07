#include "GameSystem.h"
#include "Player.h"

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

	//Test, draw Twoeyes
	twoEyes = new Player();
	gameObjects.push_back(twoEyes);
	twoEyes->Load("Player 1", "Assets/Player/p1_spritesheet.png", "twoEyes", 100, 100, 72, 97, pRenderer);
}

//System destructor, clean up SDL
GameSystem::~GameSystem()
{
	delete twoEyes;

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
	//Clear the screen
	SDL_RenderClear(pRenderer);

	//Loop through all gameobjects and draw
	for (std::vector<GameObject*>::size_type i = 0; i != gameObjects.size(); i++)
	{
		gameObjects[i]->Draw(pRenderer);
	}

	//Draw the buffer to screen
	SDL_RenderPresent(pRenderer);
}

void GameSystem::Update()
{
	//Loop through all gameobjects and update
	for (std::vector<GameObject*>::size_type i = 0; i != gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
}

void GameSystem::Print(std::string Message)
{
	//log << "(" << SDL_GetTicks() / 1000 << ") " << Message << std::endl;
	std::cout << "(" << SDL_GetTicks() / 1000 << ") " << Message << std::endl;
}

void GameSystem::Print(int Message)
{
	//log << "(" << SDL_GetTicks() / 1000 << ") " << Message << std::endl;
	std::cout << "(" << SDL_GetTicks() / 1000 << ") " << Message << std::endl;
}


void GameSystem::PrintSDLError()
{
	//log << "(" << SDL_GetTicks() / 1000 << ") " << "Error: " << std::string(SDL_GetError()) << std::endl;
	std::cout << "(" << SDL_GetTicks() / 1000 << ") " << "Error: " << std::string(SDL_GetError()) << std::endl;
}