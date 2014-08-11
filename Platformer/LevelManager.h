#pragma once
#include "GameObject.h"
#include "SpriteSheet.h"
#include "tinyxml2.h"
#include "GameTile.h"
#include "SDL.h"
#include <iostream>
#include <string>
#include <vector>


class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	//Get the level's data
	void LoadLevelData(const char* LevelPath);
	void LoadLevelSheet(const char* SheetPath);

	//Clean the level to load another
	void CleanLevel();

	//Level data containers
	std::vector<GameObject*> levelObjects;
	std::vector<GameTile*> levelTiles;

private:
	//Level name parsed in levelDoc
	std::string levelName;

	//Level spritesheet
	SpriteSheet* levelSheet;

	//Read XML and put data into containers in GameSystem for game to process
	XMLDocument levelDoc;

	//Default spawnpoint in top left corner
	SDL_Point spawnPoint;

	//Level end, default values initialized in constructor
	SDL_Rect levelEndBoundaries;
};