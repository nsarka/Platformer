#pragma once
#include "SDL.h"
#include "SpriteSheet.h"
#include "tinyxml2.h"
#include "GameTile.h"
#include "Textures.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>


class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	//Get the level's data
	void LoadLevelData(const char* ImagePath, const char* XMLPath, SDL_Renderer* pRenderer);
	void LoadLevelSheet(const char* XMLPath);

	//Get info
	std::string GetLevelName() { return levelName; }

	//Clean the level to load another
	void CleanLevel();

	//Level data containers
	std::vector<GameTile*> levelTiles;

	//Each level will have a player
	Player player;

private:
	//Level name parsed in levelDoc
	std::string levelName = "null: call LoadLevelSheet before LoadLevelData";

	//Level spritesheet
	SpriteSheet* levelSheet = 0;

	//Read XML and put data into containers in GameSystem for game to process
	XMLDocument levelDoc;

	//Default spawnpoint in top left corner
	SDL_Point spawnPoint;

	//Level end, default values initialized in constructor
	SDL_Rect levelEndBoundaries;
};