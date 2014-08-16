#include "Player.h"
#include "Camera.h"
#include "GameSystem.h"

Player::Player()
{
	playerSheet = new SpriteSheet("Assets/p2_spritesheet.xml");

	playerScreenPos.x = 1024 / 2;
	playerScreenPos.y = 768 / 2;
}

void Player::Load(std::string path, std::string texture, int x, int y, SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->LoadTexture(path, texture, pRenderer);

	textureID = texture;
	playerWorldPos.x = x;
	playerWorldPos.y = y;
}

void Player::Update()
{
	//Let him move with input
	HandleInput();

	//Let the camera follow him
	Camera::Instance()->SetFocus(playerWorldPos);
}

void Player::Draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->DrawTexture(textureID, playerScreenPos.x, playerScreenPos.y, objFrame.w, objFrame.h, objFrame.x, objFrame.y, pRenderer, playerFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Player::HandleInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	int boundsCheckX = Camera::Instance()->IsOutOfMapBoundariesX(playerWorldPos.x);
	int boundsCheckY = Camera::Instance()->IsOutOfMapBoundariesY(playerWorldPos.y);

	if (!state[SDL_SCANCODE_RIGHT] || !state[SDL_SCANCODE_LEFT])
	{
		objFrame = playerSheet->GetFrame("p2_stand");
	}

	if (state[SDL_SCANCODE_DOWN] && boundsCheckY != 2)
	{
		objFrame = playerSheet->GetFrame("p2_duck");
		playerWorldPos.y += 1;
	}

	if (state[SDL_SCANCODE_UP] && boundsCheckY != 1)
	{
		objFrame = playerSheet->GetFrame("p2_jump");
		playerWorldPos.y -= 1;
	}

	if (state[SDL_SCANCODE_LEFT] && boundsCheckX != 1)
	{
		playerWorldPos.x -= 1;
		playerFlip = true;
		objFrame = playerSheet->GetFrame(walkFrames[int(((SDL_GetTicks() / 25) % 11))]);
	}

	if (state[SDL_SCANCODE_RIGHT] && boundsCheckX != 2)
	{
		playerWorldPos.x += 1;
		playerFlip = false;
		objFrame = playerSheet->GetFrame(walkFrames[int(((SDL_GetTicks() / 25) % 11))]);
	}
}