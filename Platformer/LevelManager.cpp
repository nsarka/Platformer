#include "LevelManager.h"
#include "GameTile.h"


LevelManager::LevelManager()
{
	levelEndBoundaries.x = 0;
	levelEndBoundaries.y = 0;
	levelEndBoundaries.w = 0;
	levelEndBoundaries.h = 0;

	spawnPoint.x = 0;
	spawnPoint.y = 0;
}

void LevelManager::LoadLevelSheet(const char* SheetPath)
{
	levelSheet = new SpriteSheet(SheetPath);
}

void LevelManager::LoadLevelData(const char* LevelPath)
{
	if (levelDoc.LoadFile(LevelPath) == XML_NO_ERROR)
	{
		//Parse level data
		XMLElement* levelElement = levelDoc.FirstChildElement("leveldata");

		//Create variables to put data in
		std::string levelname;

		//Get the data
		//levelElement->QueryAttribute("name", &levelname);
		levelElement->QueryIntAttribute("spawnx", &spawnPoint.x);
		levelElement->QueryIntAttribute("spawny", &spawnPoint.y);
		levelElement->QueryIntAttribute("levelendx", &levelEndBoundaries.x);
		levelElement->QueryIntAttribute("levelendy", &levelEndBoundaries.y);
		levelElement->QueryIntAttribute("levelendw", &levelEndBoundaries.w);
		levelElement->QueryIntAttribute("levelendh", &levelEndBoundaries.h);

		//Cycle through all elements in the spritesheet
		for (tinyxml2::XMLElement* child = levelElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			GameTile tile;

			tile.textureName = std::string(child->Attribute("name"));

			child->QueryIntAttribute("posX", &tile.point.x);
			child->QueryIntAttribute("posY", &tile.point.y);
			child->QueryBoolAttribute("physics", &tile.physics);
			child->QueryIntAttribute("sound", &tile.sound);
			child->QueryBoolAttribute("action", &tile.action);

			//Add tile to list
			levelTiles.push_back(&tile);
		}
	}
	else
	{
		std::cout << "XML sheet could not be found: " << std::string(LevelPath) << std::endl;
	}
}

void LevelManager::CleanLevel()
{

}

LevelManager::~LevelManager()
{

}