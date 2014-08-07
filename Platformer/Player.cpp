#include "Player.h"
#include "Textures.h"
#include "GameSystem.h"
#include <string>

Player::Player()
{
	playerSheet = new SpriteSheet("Assets/spritesheet.xml");
	playerSheet->PrintSheet();
}

void Player::Update()
{
	Player::objFrame = playerSheet->GetFrame("p1_walk10");
}

void Player::Draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->DrawTexture(Player::textureID, Player::posX, Player::posY, Player::objFrame.w, Player::objFrame.h, Player::objFrame.x, Player::objFrame.y, pRenderer);
}
