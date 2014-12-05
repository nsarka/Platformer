#pragma once
#include "tinyxml2.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool SaveScene(); //returns success or fail
	bool LoadScene();

private:

};

