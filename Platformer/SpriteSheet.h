#pragma once
#include "tinyxml2.h"
#include "SDL.h"
#include <map>

using namespace tinyxml2;

class SpriteSheet
{
public:
	SpriteSheet(const char* Path);
	~SpriteSheet();

	//Read spritesheet data
	SDL_Rect GetFrame(std::string FrameName);

	//Print all sheet data in console
	void PrintSheet();

private:
	XMLDocument sheetDoc;
	std::map<std::string, SDL_Rect> frameMap;
};

