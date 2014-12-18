#pragma once
#include "tinyxml2.h"
#include "SpriteManager.h"
#include "Texture.h"
#include "Camera.h"
#include "Toolbar.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool SaveScene(const char* XMLPath); //returns success or fail
	bool LoadScene(const char* Path);

	void Draw(SDL_Renderer* pRenderer);

	std::string getLevelName() { return levelName;  }

private:
	//Level spritesheet
	SpriteSheet* levelSheet = 0;

	//Level data
	XMLDocument levelDoc;

	//Tile selector toolbar--member of scenemanager because toolbar is populated with tiles based on the spritesheet given for a level
	Toolbar* tileSelector;

	//Level name
	std::string levelName = "null";
};

