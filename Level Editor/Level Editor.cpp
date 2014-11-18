#include "SDL.h"
#include "EditorSystem.h"

EditorSystem* editsys = 0;

int main(int argc, char* args[])
{
	//SDL init in constructor
	editsys = new EditorSystem();

	while (editsys->Running())
	{
		editsys->HandleEvents();
		editsys->Render();
		editsys->Update();

		//Cap our framerate
		editsys->Delay();
	}

	//System destructor, clean up SDL
	delete editsys;

	return 0;
}

