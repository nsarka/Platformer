#pragma once
#include "SDL.h"

class Camera
{
public:
	static Camera* Instance()
	{
		if (!pInstance) { pInstance = new Camera(); }
		return pInstance;
	}

	//Camera follows this point
	void SetFocus(SDL_Point focus) { viewFocus = focus; };

	//Check map boundaries to stop camera if player goes too far
	int IsOutOfMapBoundariesX(int posX);
	int IsOutOfMapBoundariesY(int posY);

	//Set functions so levelmanager can put its data in the camera
	void SetCameraBoundsX(int x) { CameraBounds.x = x; }
	void SetCameraBoundsY(int y) { CameraBounds.y = y; }
	void SetCameraBoundsW(int w) { CameraBounds.w = w; }
	void SetCameraBoundsH(int h) { CameraBounds.h = h; }
	
	//Get the camera position so level tiles can scroll
	SDL_Point GetOffset();

private:
	Camera() {};
	~Camera() {};

	//Map width and height for Camera; is loaded in levelmanager->loaddata
	SDL_Rect CameraBounds;

	//What the camera looks at
	SDL_Point viewFocus;

	//Use camera as a singleton
	static Camera* pInstance;
};
