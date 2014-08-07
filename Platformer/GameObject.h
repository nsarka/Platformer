#pragma once
#include <string>
#include "SDL.h"


class GameObject
{
public:
	virtual void Load(std::string className, std::string path, std::string texture, int x, int y, int width, int height, SDL_Renderer* pRenderer);
	virtual void Draw(SDL_Renderer* pRenderer)=0;
	virtual void Update()=0;


protected:
	std::string objClassName;
	std::string textureID;

	SDL_Rect objFrame;

	int posX;
	int posY;
};