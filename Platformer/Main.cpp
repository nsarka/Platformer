#include "SDL.h"
#include "GameSystem.h"
#include "SDL_framerate.h"

GameSystem* gamesys = 0;
FPSmanager fpsManager;

int main(int arc, char* args[])
{
	//SDL init in constructor
	gamesys = new GameSystem();

	//Initialize framerate manager
	SDL_initFramerate(&fpsManager);

	//Set the framerate
	SDL_setFramerate(&fpsManager, 160);

	while(gamesys->Running())
	{
		gamesys->HandleEvents();
		gamesys->Render();
		gamesys->Update();

		//Cap our framerate
		SDL_framerateDelay(&fpsManager);
	}

	//SDL cleanup in destructor
	delete gamesys;

	return 0;
}