#pragma once
#include "GameObject.h"
#include "GameSystem.h"
#include "SpriteSheet.h"
#include "tinyxml2.h"
#include "SDL.h"
#include <string>

//todo: have level class read the spritesheet, read the levelDoc, then draw sprites on the sheet according to levelDoc
class Level
{
public:
	Level();
	~Level();

	void Update();
	void Draw(SDL_Renderer* pRenderer);

	//Get the level's data
	void LoadLevelData(const char* levelPath);
	void LoadLevelSheet(const char* SheetPath);

private:
	//Level name parsed in levelDoc
	std::string levelName;

	SpriteSheet* levelSheet = 0;

	XMLDocument levelDoc;
	XMLDocument sheetDoc;

	//Tilemap container
	std::map<std::string, SDL_Rect> tileMap;

	//Default spawnpoint in lower left corner
	int spawnX = 100;
	int spawnY = 500;

	//Level end
	SDL_Rect levelEndBoundaries;
};