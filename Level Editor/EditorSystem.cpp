#include "EditorSystem.h"

//System constructer, init SDL
EditorSystem::EditorSystem()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//Keep window at 1024x768
	pWindow = SDL_CreateWindow("Platformer Level Editor by Magnolium", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	//Set the default draw color to a sky color
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);

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
}

//System destructor, clean up SDL
EditorSystem::~EditorSystem()
{
	TTF_CloseFont(GameOverFont);
	GameOverFont = NULL;
	TTF_Quit();

	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
}

void EditorSystem::HandleEvents()
{
	SDL_Event Event;

	if (SDL_PollEvent(&Event))
	{
		switch (Event.type)
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
				//Change level
				std::cout << "Enter level name (i.e. level02)" << std::endl;

				std::string levelname;
				std::cin >> levelname;

				std::cout << "Loading " << levelname << ".xml" << std::endl;

				std::string levelstring = "Assets/" + levelname + ".xml";

				//do something with levelstring
				sceneManager.LoadScene(levelstring.c_str());
			}

			if (Event.key.keysym.sym == SDLK_F3)
			{
				//Change level
				std::cout << "Enter level name (i.e. level02)" << std::endl;

				std::string levelname;
				std::cin >> levelname;

				std::cout << "Loading " << levelname << ".xml" << std::endl;

				std::string levelstring = "Assets/" + levelname + ".xml";

				//do something with levelstring
				sceneManager.SaveScene(levelstring.c_str());
			}
			break;

		default:
			break;
		}
	}
}

void EditorSystem::Render()
{
	//Clear the screen
	SDL_RenderClear(pRenderer);



	//Render debug text
	if (bDebugInfo) { DrawText(DebugString); }

	//Draw the buffer to screen
	SDL_RenderPresent(pRenderer);
}

void EditorSystem::Update()
{
	//Update debug text's player coords, fps, level name, etc.
	UpdateDebugText();
}

void EditorSystem::DrawText(std::string TextString)
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

void EditorSystem::UpdateDebugText()
{
	//Set the debug text string
	if (bDebugInfo)
	{
		//String would get big really fast if we didnt reset it
		DebugString = "Level: ";
		DebugString.append(sceneManager.getLevelName());

		DebugString.append("\nGame FPS: ");
		DebugString.append(std::to_string(SDL_getFramerate(&fpsManager)));
	}
}

void EditorSystem::Delay()
{
	//Cap our framerate
	SDL_framerateDelay(&fpsManager);
}