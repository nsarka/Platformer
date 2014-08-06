#include "Player.h"
#include "Textures.h"
#include <iostream>

void Player::Update()
{
	posX += 1;
}

void Player::Draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->DrawTexture(Player::textureID, Player::posX, Player::posY, Player::objWidth, Player::objHeight, pRenderer);
	std::cout << Player::posX << " " << Player::posY << "\n";
}
