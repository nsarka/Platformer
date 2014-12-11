#pragma once
#include "tinyxml2.h"
#include "SpriteManager.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool SaveScene(const char* XMLPath); //returns success or fail
	bool LoadScene(const char* XMLPath);

	std::string getLevelName() { return levelName;  }

private:
	//Level spritesheet
	SpriteSheet* levelSheet = 0;

	//Level name
	std::string levelName = "null";
};

