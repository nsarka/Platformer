#include "Textures.h"
#include "SDL_image.h"

TextureManager* TextureManager::pInstance = 0;

bool TextureManager::LoadTexture(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{
		return false;
	}

	SDL_Texture* pTexture =
	SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	//Everything went ok, add the texture to our list
	if (pTexture != 0)
	{
		textureMap[id] = pTexture;
		return true;
	}

	//Reaching here means something went wrong
	return false;
}

void TextureManager::DrawTexture(std::string id, int destX, int destY, int width, int height, int srcX, int srcY, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = destX;
	destRect.y = destY;

	SDL_RenderCopyEx(pRenderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}