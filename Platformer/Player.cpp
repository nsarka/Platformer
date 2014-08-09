#include "Player.h"
#include "Textures.h"
#include "GameSystem.h"
#include <string>

Player::Player()
{
	playerSheet = new SpriteSheet("Assets/p2_spritesheet.xml");
}

void Player::Update()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (!state[SDL_SCANCODE_RIGHT] || !state[SDL_SCANCODE_LEFT])
	{
		Player::objFrame = playerSheet->GetFrame("p2_stand");
	}

	if (!state[SDL_SCANCODE_RIGHT] || !state[SDL_SCANCODE_LEFT] || !state[SDL_SCANCODE_UP])
	{
		if (state[SDL_SCANCODE_DOWN])
		{
			Player::objFrame = playerSheet->GetFrame("p2_duck");
			Player::posY += 1;
		}
	}

	if (!state[SDL_SCANCODE_RIGHT] || !state[SDL_SCANCODE_LEFT] || !state[SDL_SCANCODE_DOWN])
	{
		if (state[SDL_SCANCODE_UP])
		{
			Player::objFrame = playerSheet->GetFrame("p2_jump");
			Player::posY -= 1;
		}
	}

	if (state[SDL_SCANCODE_LEFT])
	{
		Player::posX -= 1;
		playerFlip = true;
		Player::objFrame = playerSheet->GetFrame(walkFrames[int(((SDL_GetTicks() / 25) % 11))]);
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		Player::posX += 1;
		playerFlip = false;
		Player::objFrame = playerSheet->GetFrame(walkFrames[int(((SDL_GetTicks() / 25) % 11))]);
	}
}

void Player::Draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->DrawTexture(Player::textureID, Player::posX, Player::posY, Player::objFrame.w, Player::objFrame.h, Player::objFrame.x, Player::objFrame.y, pRenderer, playerFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
