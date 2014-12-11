#include "SpriteManager.h"
#include "EditorSystem.h"
#include <iostream>


SpriteSheet::SpriteSheet(const char* Path)
{
	if (sheetDoc.LoadFile(Path) == XML_NO_ERROR)
	{
		XMLElement* frameElement = sheetDoc.FirstChildElement("spritesheet");

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
		std::cout << "XML sheet could not be found: " << std::string(Path) << std::endl;
	}
}


SDL_Rect SpriteSheet::GetFrame(std::string FrameName)
{
	if (frameMap.find(FrameName) == frameMap.end())
	{
		std::cout << "Frame " << std::string(FrameName) << " not found in spritesheet" << std::endl;

		//Just to stop compiler warning
		SDL_Rect rect = { 0, 0, 0, 0 };
		return rect;
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
		std::cout << i->first << ": ";
		std::cout << i->second.x << std::endl;
	}
}


SpriteSheet::~SpriteSheet()
{

}