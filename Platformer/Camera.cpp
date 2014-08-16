#include "Camera.h"

Camera* Camera::pInstance = 0;

SDL_Point Camera::GetOffset()
{
	SDL_Point pos;

	//512 is screen width / 2
	pos.x = viewFocus.x - 512;

	//Screen height / 2 = 384
	pos.y = viewFocus.y - 384;

	return pos;
}

//If the point is too far left or right, hes out of the map
int Camera::IsOutOfMapBoundariesX(int posX)
{
	if (posX <= CameraBounds.x)
	{
		//Too far left
		return 1;
	}

	else if (posX >= (CameraBounds.x + CameraBounds.w))
	{
		//Too far right
		return 2;
	}

	//If its none of the above hes in bounds
	return 0;
}

//If the point is too far up or down, hes out of the map
int Camera::IsOutOfMapBoundariesY(int posY)
{
	if (posY <= CameraBounds.y)
	{
		//Too high up
		return 1;
	}
	else if (posY >= (CameraBounds.y + CameraBounds.h))
	{
		//Too far down
		return 2;
	}

	//If its none of the above hes in bounds
	return 0;
}