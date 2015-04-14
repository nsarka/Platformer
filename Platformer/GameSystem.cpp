#include "GameSystem.h"
#include "Util.h"

//System constructer, init SDL
GameSystem::GameSystem()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//Keep window at 1024x768
	pWindow = SDL_CreateWindow("Platformer by Magnolium", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	//Initialize framerate manager
	SDL_initFramerate(&fpsManager);

	//Set the framerate
	SDL_setFramerate(&fpsManager, 100);

	//Init sdl_ttf to draw text on screen
	if (TTF_Init() == 0)
	{
		// load font at size 32 into GameOverFont
		GameOverFont = TTF_OpenFont("Assets/Fonts/game_over.ttf", 32);

		if (!GameOverFont)
		{
			std::cout << "font failed to load: " << TTF_GetError() << std::endl;
		}
		else
		{
			//Set the hud text to white
			TextColor.r = 255;
			TextColor.g = 255;
			TextColor.b = 255;
			TextColor.a = 255;
		}
	}
	else
	{
		std::cout << "SDL_ttf failed to init" << std::endl;
	}

	//Keep game loop running
	bRunning = true;

	//Load splash and main menu
	Menu.LoadSplash(pRenderer);
	Menu.isInMenu = true;

	//Initialize the level; Each level owns and loads all LevelObjects and GameObjects, GameSystem class only owns a vector list of the two
	levelManager.LoadLevelSheet("Assets/tileset_spritesheet.xml");
	levelManager.LoadLevelData("Assets/Tiles/tiles_spritesheet.png", "Assets/level01.xml", pRenderer, false);

	//Set sky color
	SDL_SetRenderDrawColor(pRenderer, levelManager.colors.r, levelManager.colors.g, levelManager.colors.b, levelManager.colors.a);
}

//System destructor, clean up SDL
GameSystem::~GameSystem()
{
	TTF_CloseFont(GameOverFont);
	GameOverFont = NULL;
	TTF_Quit();

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

		case SDL_KEYDOWN:
			if (Event.key.keysym.sym == SDLK_F1)
			{
				ToggleDebugInfo();
			}

			if (Event.key.keysym.sym == SDLK_F2)
			{
				//This pauses the game
				std::cout << "Load level name (i.e. level02)" << std::endl;

				std::string levelname;
				std::cin >> levelname;

				std::cout << "Loading " << levelname << ".xml" << std::endl;

				std::string levelstring = "Assets/" + levelname + ".xml";

				levelManager.CleanLevel();
				levelManager.LoadLevelSheet("Assets/tileset_spritesheet.xml");
				levelManager.LoadLevelData("Assets/Tiles/tiles_spritesheet.png", levelstring.c_str(), pRenderer, true);
			}

			if (Event.key.keysym.sym == SDLK_F3)
			{
				//This pauses the game
				std::cout << "Save level name (i.e. level02)" << std::endl;

				std::string levelname;
				std::cin >> levelname;

				std::cout << "Saving " << levelname << ".xml" << std::endl;

				std::string levelstring = "Assets/" + levelname + ".xml";

				levelManager.SaveLevel(levelstring) ? std::cout << "Saved." << std::endl : std::cout << "Not Saved." << std::endl;
			}

			if (Event.key.keysym.sym == SDLK_F4)
			{
				ToggleSandboxMode();
			}

		case SDL_MOUSEBUTTONDOWN:
			if (Menu.isInMenu)
			{
				Menu.isInMenu = false;
			}
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

	if (!Menu.isInMenu)
	{
		//Render all tiles by looping through all the levels tiles and drawing
		for (std::vector<GameTile*>::size_type i = 0; i != levelManager.levelTiles.size(); i++)
		{
			levelManager.levelTiles[i]->Draw(pRenderer, bDebugInfo);
		}

		//Render Player
		levelManager.player.Draw(pRenderer, bDebugInfo);

		//Render debug text
		if (bDebugInfo) { DrawText(DebugString); }
	}
	else
	{
		Menu.Draw(pRenderer);
	}

	//Draw the buffer to screen
	SDL_RenderPresent(pRenderer);
}

void GameSystem::Update()
{
	if (!Menu.isInMenu)
	{
		//Update debug text's player coords, fps, level name, etc.
		UpdateDebugText();

		//Update the physics world
		levelManager.world->Step(levelManager.timeStep, levelManager.velocityIterations, levelManager.positionIterations);

		//Update all tiles by looping through them
		for (std::vector<GameTile*>::size_type i = 0; i != levelManager.levelTiles.size(); i++)
		{
			levelManager.levelTiles[i]->Update();
		}

		//Get player input, move player, etc.
		levelManager.player.Update();
	}
}

void GameSystem::DrawText(std::string TextString)
{
	//Create the text surface
	SDL_Surface* TextSurface = TTF_RenderText_Blended_Wrapped(GameOverFont, TextString.c_str(), TextColor, 150);

	//Make a texture out of it
	SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(pRenderer, TextSurface);

	//Free the surface from memory
	SDL_FreeSurface(TextSurface);

	//Create a destination rectangle the text will go in
	int textureW = 0;
	int textureH = 0;

	SDL_QueryTexture(TextTexture, NULL, NULL, &textureW, &textureH);
	SDL_Rect DRect = { 0, 0, textureW, textureH };

	//Copy it to the renderer
	SDL_RenderCopy(pRenderer, TextTexture, NULL, &DRect);

	//Free the texture from memory
	SDL_DestroyTexture(TextTexture);
}

void GameSystem::UpdateDebugText()
{
	//Set the debug text string
	if (bDebugInfo)
	{
		//String would get big really fast if we didnt reset it
		DebugString = "Level: ";
		DebugString.append(levelManager.GetLevelName());

		DebugString.append("\nSandbox Mode: ");
		DebugString.append(std::to_string(bSandboxMode));

		DebugString.append("\nGame FPS: ");
		DebugString.append(std::to_string(SDL_getFramerate(&fpsManager)));

		DebugString.append("\nWorld X: ");
		DebugString.append(std::to_string(levelManager.player.GetWorldPosX()));

		DebugString.append("\nWorld Y: ");
		DebugString.append(std::to_string(levelManager.player.GetWorldPosY()));

		DebugString.append("\nFoot Sensor: ");
		DebugString.append(std::to_string(levelManager.player.numFootContacts));

		DebugString.append("\nSprinting: ");
		DebugString.append(std::to_string(levelManager.player.GetPlayerSprint()));

		DebugString.append("\nVelocity: ");
		DebugString.append(std::to_string(levelManager.player.GetPlayerVelocity().x));
		DebugString.append(" ");
		DebugString.append(std::to_string(levelManager.player.GetPlayerVelocity().y));
	}
}

void GameSystem::Delay()
{
	//Cap our framerate
	SDL_framerateDelay(&fpsManager);
}