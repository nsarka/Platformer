#pragma once
#include <map>
#include "SDL.h"


class TextureManager
{
public:
	static TextureManager* Instance()
	{
		if (!pInstance) { pInstance = new TextureManager(); }
		return pInstance;
	}

	bool LoadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void DrawTexture(std::string id, int destX, int destY, int width, int height, int srcX, int srcY, float angle, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	TextureManager() {}
	~TextureManager() {}

	//Rectangles for drawing
	SDL_Rect srcRect;
	SDL_Rect destRect;

	//Container for mapping texture name to texture
	std::map<std::string, SDL_Texture*> textureMap;

	//Use TextureManager class as a singleton
	static TextureManager* pInstance;
};