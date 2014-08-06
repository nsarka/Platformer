#pragma once
#include <map>
#include "SDL.h"


class TextureManager
{
public:
	~TextureManager() {}

	bool LoadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void DrawTexture(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static TextureManager* Instance()
	{
		if (!pInstance) { pInstance = new TextureManager(); }
		return pInstance;
	}

private:
	TextureManager() {}

	//Use TextureManager class as a singleton
	static TextureManager* pInstance;

	std::map<std::string, SDL_Texture*> textureMap;
};