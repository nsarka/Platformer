#pragma once
#include "SDL.h"

class Camera
{
public:
	static Camera* Instance()
	{
		if (!pInstance)
		{
			pInstance = new Camera();
			pInstance->viewDrift.x = 0;
			pInstance->viewDrift.y = 0;
		}
		return pInstance;
	}

	//Camera follows this point
	void SetFocus(SDL_Point focus) { viewFocus = focus; };

	//Set drift
	void SetDrift(SDL_Point drift) { viewDrift = drift; };

	//Check map boundaries to stop camera if player goes too far
	int IsOutOfMapBoundariesX(int posX);
	int IsOutOfMapBoundariesY(int posY);

	//Set functions so levelmanager can put its data in the camera
	void SetCameraBoundsX(int x) { CameraBounds.x = x; }
	void SetCameraBoundsY(int y) { CameraBounds.y = y; }
	void SetCameraBoundsW(int w) { CameraBounds.w = w; }
	void SetCameraBoundsH(int h) { CameraBounds.h = h; }

	//Get if hes in the middle (no drift)
	bool IsCentered();

	//Get the camera position so level tiles can scroll
	SDL_Point GetOffset();

	//Get the camera position with drift
	SDL_Point GetOffsetDrift();

private:
	Camera() {};
	~Camera() {};

	//Map width and height for Camera; is loaded in levelmanager->loaddata
	SDL_Rect CameraBounds;

	//What the camera looks at
	SDL_Point viewFocus;

	//Camera drift
	SDL_Point viewDrift;

	//Use camera as a singleton
	static Camera* pInstance;
};