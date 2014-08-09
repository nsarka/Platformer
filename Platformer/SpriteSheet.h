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

	SDL_Rect GetFrame(std::string FrameName);

	void PrintSheet();

private:
	XMLDocument sheetDoc;
	std::map<std::string, SDL_Rect> frameMap;
};

