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
#include "Box2d.h"
#include "ContactListener.h"


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

	//And a world
	b2World* world = 0;
	float32 timeStep = 1.0f / 100.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	float sc = 16.0;

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

	//Contact listener
	ContactListener* TheContactListener = 0;
};