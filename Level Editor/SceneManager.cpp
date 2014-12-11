#include "SceneManager.h"

SceneManager::SceneManager()
{

}

bool SceneManager::LoadScene(const char* XMLPath)
{
	levelSheet = new SpriteSheet(XMLPath);
	return true;
}

bool SceneManager::SaveScene(const char* XMLPath)
{
	return true;
}

SceneManager::~SceneManager()
{

}
