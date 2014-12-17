#include "Mainmenu.h"
#include "Textures.h"

void Mainmenu::LoadSplash(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->LoadTexture(std::string("Assets/Background/background.png"), "splash", pRenderer);
}

void Mainmenu::Draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->DrawTexture("splash", NULL, NULL, 1024, 768, NULL, NULL, 0.0, pRenderer, SDL_FLIP_NONE);
}
