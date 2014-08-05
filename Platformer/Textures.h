#ifndef __Textures__
#define __Textures__

#include <map>
#include "SDL.h"

class TextureManager
{
public:
	TextureManager() {}
	~TextureManager() {}

	bool LoadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void DrawTexture(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	std::map<std::string, SDL_Texture*> m_textureMap;
};


#endif