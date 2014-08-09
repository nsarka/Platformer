#include "Level.h"


Level::Level()
{

}

void Level::LoadLevelData(const char* levelPath)
{
	if (levelDoc.LoadFile(levelPath) == XML_NO_ERROR)
	{
		//Parse level data
	}
	else
	{
		GameSystem::Print("XML sheet could not be found");
		GameSystem::Print(std::string(levelPath));
	}
}

void Level::LoadLevelSheet(const char* SheetPath)
{
	levelSheet = new SpriteSheet(SheetPath);

	if (levelDoc.LoadFile(SheetPath) == XML_NO_ERROR)
	{
		XMLElement* frameElement = levelDoc.FirstChildElement("spritesheet");

		//Cycle through all elements in the spritesheet
		for (tinyxml2::XMLElement* child = frameElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			SDL_Rect rect;

			child->QueryIntAttribute("xpos", &rect.x);
			child->QueryIntAttribute("ypos", &rect.y);
			child->QueryIntAttribute("width", &rect.w);
			child->QueryIntAttribute("height", &rect.h);

			tileMap[std::string(child->Name())] = rect;
		}
	}
	else
	{
		GameSystem::Print("XML sheet could not be found");
		GameSystem::Print(std::string(SheetPath));
	}
}

void Level::Update()
{

}

void Level::Draw(SDL_Renderer* pRenderer)
{

}

Level::~Level()
{

}