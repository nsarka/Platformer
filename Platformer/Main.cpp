#include "SDL.h"
#include "GameSystem.h"

GameSystem* gamesys = 0;

int main(int arc, char* args[])
{
	//SDL init in constructor
	gamesys = new GameSystem();

	while(gamesys->Running())
	{
		gamesys->HandleEvents();
		gamesys->Render();
		gamesys->Update();

		//Cap our framerate
		gamesys->Delay();
	}

	//System destructor, clean up SDL
	delete gamesys;

	return 0;
}