#include "GameTile.h"
#include "LevelManager.h"

GameTile::GameTile()
{

}

void GameTile::Draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->DrawTexture(textureName, point.x, point.y, frame.w, frame.h, frame.x, frame.y, pRenderer, SDL_FLIP_NONE);
}

GameTile::~GameTile()
{

}
