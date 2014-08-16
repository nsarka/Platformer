#include "GameTile.h"
#include "Camera.h"

GameTile::GameTile()
{

}

void GameTile::Draw(SDL_Renderer* pRenderer)
{
	if (IsTileInScreen(point.x - Camera::Instance()->GetOffset().x, point.y - Camera::Instance()->GetOffset().y, frame.w, frame.h))
	{
		//Subtract camera offset so the tiles scroll
		TextureManager::Instance()->DrawTexture(ImageName, point.x - Camera::Instance()->GetOffset().x, point.y - Camera::Instance()->GetOffset().y, frame.w, frame.h, frame.x, frame.y, pRenderer, SDL_FLIP_NONE);
	}
}

bool GameTile::IsTileInScreen(int x, int y, int w, int h)
{
	//x + w because we want to check to the right corners, not the left
	if(x + w <= 0)
	{
		return false;
	}

	//Same thing for y but for height
	if (y + h <= 0)
	{
		return false;
	}

	if (x >= 1024)
	{
		return false;
	}

	if (y >= 768)
	{
		return false;
	}

	return true;
}

void GameTile::SetFrame(SDL_Rect Frame)
{
	frame = Frame;
}

void GameTile::SetImageName(std::string TextureName)
{
	ImageName = TextureName;
}

void GameTile::SetTileName(std::string TileName)
{
	TileName = TileName;
}

void GameTile::SetPoint(SDL_Point Point)
{
	point = Point;
}

void GameTile::SetPhysics(int Physics)
{
	physics = Physics;
}

void GameTile::SetSound(int Sound)
{
	sound = Sound;
}

void GameTile::SetAction(bool Action)
{
	action = Action;
}

GameTile::~GameTile()
{

}
