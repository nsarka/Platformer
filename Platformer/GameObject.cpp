#include "GameObject.h"
#include "Textures.h"

void GameObject::Load(std::string className, std::string path, std::string texture, int x, int y, int framewidth, int frameheight, SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->LoadTexture(path, texture, pRenderer);

	objClassName = className;
	textureID = texture;

	posX = x;
	posY = y;
	objFrame.w = framewidth;
	objFrame.h = frameheight;
}