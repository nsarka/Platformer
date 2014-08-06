#include "Player.h"
#include "Textures.h"
#include "GameSystem.h"
#include <string>

void Player::Update()
{
	//update frame
}

void Player::Draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->DrawTexture(Player::textureID, Player::posX, Player::posY, Player::objWidth, Player::objHeight, Player::srcX, Player::srcY, pRenderer);
}
