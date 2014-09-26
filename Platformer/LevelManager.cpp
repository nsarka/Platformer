#include "LevelManager.h"
#include "Camera.h"


LevelManager::LevelManager()
{
	levelEndBoundaries.x = 0;
	levelEndBoundaries.y = 0;
	levelEndBoundaries.w = 0;
	levelEndBoundaries.h = 0;

	spawnPoint.x = 0;
	spawnPoint.y = 0;

	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);
}

void LevelManager::LoadLevelSheet(const char* XMLPath)
{
	levelSheet = new SpriteSheet(XMLPath);
}

void LevelManager::LoadLevelData(const char* ImagePath, const char* XMLPath, SDL_Renderer* pRenderer)
{
	if (levelDoc.LoadFile(XMLPath) == XML_NO_ERROR)
	{
		//Parse level data
		XMLElement* levelElement = levelDoc.FirstChildElement("leveldata");

		//Get the data
		levelName = std::string(levelElement->Attribute("name"));

		//Load the level's spritesheet image and give it the same name as the level
		TextureManager::Instance()->LoadTexture(std::string(ImagePath), levelName, pRenderer);

		//Get the rest of the level's info
		levelElement->QueryIntAttribute("spawnx", &spawnPoint.x);
		levelElement->QueryIntAttribute("spawny", &spawnPoint.y);

		//Put map boundaries into camera class
		SDL_Rect mapBoundaries;

		levelElement->QueryIntAttribute("mapx", &mapBoundaries.x);
		levelElement->QueryIntAttribute("mapy", &mapBoundaries.y);
		levelElement->QueryIntAttribute("mapw", &mapBoundaries.w);
		levelElement->QueryIntAttribute("maph", &mapBoundaries.h);

		//Camera bounds and map boundaries are the same thing
		Camera::Instance()->SetCameraBoundsX(mapBoundaries.x);
		Camera::Instance()->SetCameraBoundsY(mapBoundaries.y);
		Camera::Instance()->SetCameraBoundsW(mapBoundaries.w);
		Camera::Instance()->SetCameraBoundsH(mapBoundaries.h);

		//Get the end boundaries so the game knows when the player has won
		levelElement->QueryIntAttribute("levelendx", &levelEndBoundaries.x);
		levelElement->QueryIntAttribute("levelendy", &levelEndBoundaries.y);
		levelElement->QueryIntAttribute("levelendw", &levelEndBoundaries.w);
		levelElement->QueryIntAttribute("levelendh", &levelEndBoundaries.h);

		//Cycle through all elements in the spritesheet
		for (tinyxml2::XMLElement* child = levelElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			//Create a new tile to add to our master tile list
			GameTile* tile = new GameTile();
			SDL_Point point;
			std::string tileName;
			int physics;
			int sound;
			bool action;
			SDL_Rect rect;

			//Read XML document to get this info
			tileName = std::string(child->Attribute("name"));
			child->QueryIntAttribute("posX", &point.x);
			child->QueryIntAttribute("posY", &point.y);
			child->QueryIntAttribute("physics", &physics);
			child->QueryIntAttribute("sound", &sound);
			child->QueryBoolAttribute("action", &action);

			//Get the frame info from the spritesheet by name
			rect = levelSheet->GetFrame(tileName);

			//Set the tiles information
			tile->SetTileName(tileName);
			tile->SetImageName(levelName);
			tile->SetPoint(point);
			tile->SetFrame(rect);
			tile->SetPhysics(physics, world);
			tile->SetSound(sound);
			tile->SetAction(action);

			//Add tile to list
			levelTiles.push_back(tile);
		}

		//Level is done, create player
		player.Load("Assets/Player/p1_spritesheet.png", "playertexture", spawnPoint.x, spawnPoint.y, pRenderer, world);

		//Player is made, set up the contact listener
		TheContactListener = new ContactListener(player.numFootContacts);
		world->SetContactListener(TheContactListener);

		//Set the cameras position by dividing by the scale and focusing
		spawnPoint.x = spawnPoint.x / sc;
		spawnPoint.y = spawnPoint.y / sc;
		Camera::Instance()->SetFocus(spawnPoint);
	}
	else
	{
		std::cout << "XML sheet could not be found: " << std::string(XMLPath) << std::endl;
	}
}

void LevelManager::CleanLevel()
{
	//Clear tile map, save player coords
}

LevelManager::~LevelManager()
{

}