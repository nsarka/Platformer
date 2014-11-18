#include "SDL.h"
#include "EditorSystem.h"

EditorSystem* gamesys = 0;

int main(int argc, char* args[])
{
	//SDL init in constructor
	gamesys = new EditorSystem();

	while (gamesys->Running())
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

