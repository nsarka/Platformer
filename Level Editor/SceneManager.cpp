#include "SceneManager.h"


SceneManager::SceneManager()
{
	//Set up the tile selector toolbar
	tileSelector = new Toolbar(100, 100, 100, 100);
}

void SceneManager::Draw(SDL_Renderer* pRenderer)
{

}

//Query level document for the tiles, skip physics
bool SceneManager::LoadScene(const char* Path)
{
	levelSheet = new SpriteSheet(Path);

	return true;
}

//Save the scene to .xml
bool SceneManager::SaveScene(const char* XMLPath)
{
	return true;
}

SceneManager::~SceneManager()
{

}
