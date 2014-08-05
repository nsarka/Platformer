#include "SDL.h"
#include "GameSystem.h"

GameSystem* gamesys = 0; //test

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
		SDL_Delay(10);
	}

	//SDL cleanup in destructor
	delete gamesys;

	return 0;
}