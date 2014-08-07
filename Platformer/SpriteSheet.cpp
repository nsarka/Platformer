#include "SpriteSheet.h"
#include "GameSystem.h"
#include <iostream>


SpriteSheet::SpriteSheet(const char* Path)
{
	if (doc.LoadFile(Path) == XML_NO_ERROR)
	{
		XMLElement* frameElement = doc.FirstChildElement("spritesheet");

		//Cycle through all elements in the spritesheet
		for (tinyxml2::XMLElement* child = frameElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			SDL_Rect rect;

			child->QueryIntAttribute("xpos", &rect.x);
			child->QueryIntAttribute("ypos", &rect.y);
			child->QueryIntAttribute("width", &rect.w);
			child->QueryIntAttribute("height", &rect.h);

			frameMap[std::string(child->Name())] = rect;
		}
	}
	else
	{
		GameSystem::Print("XML sheet could not be found");
		GameSystem::Print(std::string(Path));
	}
}


SDL_Rect SpriteSheet::GetFrame(std::string FrameName)
{
	if (frameMap.find(FrameName) == frameMap.end())
	{
		GameSystem::Print("Frame could not be found in spritesheet");
		GameSystem::Print(FrameName);
	}
	else
	{
		return frameMap[FrameName];
	}
	
}

void SpriteSheet::PrintSheet()
{
	for (auto i = frameMap.begin(); i != frameMap.end(); ++i)
	{
		GameSystem::Print(i->first);
		GameSystem::Print(i->second.x);
		GameSystem::Print(" ");
	}
}


SpriteSheet::~SpriteSheet()
{

}