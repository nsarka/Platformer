#include "GameSystem.h"
#include "Player.h"

//System constructer, init SDL
GameSystem::GameSystem()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	pWindow = SDL_CreateWindow("Platformer by Magnolium", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	//Set the default draw color to a sky color
	SDL_SetRenderDrawColor(pRenderer, 208, 244, 247, 255);

	bRunning = true;

	//Initialize the level
	levelManager.LoadLevelSheet("Assets/tileset_spritesheet.xml");
	levelManager.LoadLevelData("Assets/level01.xml");

	//Load TwoEyes
	twoEyes = new Player();
	levelManager.levelObjects.push_back(twoEyes);
	twoEyes->Load("Player 1", "Assets/Player/p2_spritesheet.png", "twoEyes", 300, 300, 72, 97, pRenderer);
}

//System destructor, clean up SDL
GameSystem::~GameSystem()
{
	delete twoEyes;

	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
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

	//Loop through all the levels tiles and draw
	for (std::vector<GameTile>::size_type i = 0; i != levelManager.levelTiles.size(); i++)
	{
		levelManager.levelTiles[i]->Draw(pRenderer);
		//std::cout << levelManager.levelTiles[i]->textureName << std::endl;
	}

	//Loop through all gameobjects and draw
	for (std::vector<GameObject*>::size_type i = 0; i != levelManager.levelObjects.size(); i++)
	{
		levelManager.levelObjects[i]->Draw(pRenderer);
	}

	//Draw the buffer to screen
	SDL_RenderPresent(pRenderer);
}

void GameSystem::Update()
{
	//Loop through all gameobjects and update
	for (std::vector<GameObject*>::size_type i = 0; i != levelManager.levelObjects.size(); i++)
	{
		levelManager.levelObjects[i]->Update();
	}
}