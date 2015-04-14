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
	pEditorBar = new Toolbar(levelSheet);
}

void LevelManager::LoadLevelData(const char* ImagePath, const char* XMLPath, SDL_Renderer* pRenderer, bool playerExists)
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

		//Query sky color
		levelElement->QueryIntAttribute("skyr", (int*)&colors.r);
		levelElement->QueryIntAttribute("skyg", (int*)&colors.g);
		levelElement->QueryIntAttribute("skyb", (int*)&colors.b);
		levelElement->QueryIntAttribute("skya", (int*)&colors.a);

		//Cycle through all elements in the spritesheet
		for (tinyxml2::XMLElement* child = levelElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			if (std::string(child->Name()) == "tile")
			{
				//Create a new tile to add to our master tile list
				GameTile* tile = new GameTile(colors.r, colors.g, colors.b, colors.a);
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

			if (std::string(child->Name()) == "joint_revolute")
			{
				//Do the bodies collide?
				bool collide_connected;

				//Limit range of joint?
				bool enable_limit, enable_motor;

				//Local anchors and joint angle limits
				float laax, laay, labx, laby;
				int upperLimit, lowerLimit, motor_speed, motor_torque;

				//Get the data
				child->QueryFloatAttribute("localanchor_a_x", &laax);
				child->QueryFloatAttribute("localanchor_a_y", &laay);
				child->QueryFloatAttribute("localanchor_b_x", &labx);
				child->QueryFloatAttribute("localanchor_b_y", &laby);
				child->QueryBoolAttribute("collide_connected", &collide_connected);
				child->QueryBoolAttribute("enable_limit", &enable_limit);
				child->QueryIntAttribute("upperlimit", &upperLimit);
				child->QueryIntAttribute("lowerlimit", &lowerLimit);
				child->QueryBoolAttribute("enable_motor", &enable_motor);
				child->QueryIntAttribute("motor_speed", &motor_speed);
				child->QueryIntAttribute("motor_torque", &motor_torque);

				/*	Get the next two tile's infomation, construct them, and return a
					handle to the physics body so we can create the joint	*/
				child = child->NextSiblingElement();

				if (std::string(child->Name()) == "tile")
				{
					//Create a new tile to add to our master tile list
					GameTile* tile = new GameTile((Uint8)colors.r, (Uint8)colors.g, (Uint8)colors.b, (Uint8)colors.a);
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
					//omitted tile->SetPhysics to get a handle to the body
					tile->SetSound(sound);
					tile->SetAction(action);

					//Add to list
					levelTiles.push_back(tile);

					//Do it again for body B
					child = child->NextSiblingElement();

					if (std::string(child->Name()) == "tile")
					{
						//Create a new tile to add to our master tile list
						GameTile* tileB = new GameTile((Uint8)colors.r, (Uint8)colors.g, (Uint8)colors.b, (Uint8)colors.a);

						int physicsB;

						//Read XML document to get this info
						tileName = std::string(child->Attribute("name"));
						child->QueryIntAttribute("posX", &point.x);
						child->QueryIntAttribute("posY", &point.y);
						child->QueryIntAttribute("physics", &physicsB);
						child->QueryIntAttribute("sound", &sound);
						child->QueryBoolAttribute("action", &action);

						//Get the frame info from the spritesheet by name
						rect = levelSheet->GetFrame(tileName);

						//Set the tiles information
						tileB->SetTileName(tileName);
						tileB->SetImageName(levelName);
						tileB->SetPoint(point);
						tileB->SetFrame(rect);
						//omitted tile->SetPhysics to get a handle to the body
						tileB->SetSound(sound);
						tileB->SetAction(action);

						//Add to list
						levelTiles.push_back(tileB);

						//Make the joint
						b2Joint* joint = 0;
						b2RevoluteJointDef revoluteJointDef;

						revoluteJointDef.bodyA = tile->SetPhysics(physics, world);
						revoluteJointDef.bodyB = tileB->SetPhysics(physicsB, world);
						revoluteJointDef.collideConnected = collide_connected;
						revoluteJointDef.enableLimit = enable_limit;
						revoluteJointDef.lowerAngle = lowerLimit * DEGTORAD;
						revoluteJointDef.upperAngle = upperLimit * DEGTORAD;
						revoluteJointDef.localAnchorA.Set(laax, laay);
						revoluteJointDef.localAnchorB.Set(labx, laby);
						revoluteJointDef.enableMotor = enable_motor;
						revoluteJointDef.maxMotorTorque = (float32)motor_torque;
						revoluteJointDef.motorSpeed = (float32)motor_speed * DEGTORAD;//degrees per second

						joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
						levelJoints.push_back(joint);
					}
					else
					{
						std::cout << "Error: Next two lines in level source need to be tiles; joint not created";
					}
				}
				else
				{
					std::cout << "Error: Next two lines in level source need to be tiles; joint not created";
				}
			}
		}

		//Level is done, create player
		if (!playerExists)
		{
			player.Load("Assets/Player/p1_spritesheet.png", "playertexture", spawnPoint.x, spawnPoint.y, pRenderer, world);
		}

		//setsky makes the sky the right color when debugdraw is used
		player.SetSky((Uint8)colors.r, (Uint8)colors.g, (Uint8)colors.b, (Uint8)colors.a);
		SDL_SetRenderDrawColor(pRenderer, (Uint8)colors.r, (Uint8)colors.g, (Uint8)colors.b, (Uint8)colors.a);

		//Player is made, set up the contact listener
		TheContactListener = new ContactListener(player.numFootContacts);
		world->SetContactListener(TheContactListener);

		//Set the cameras position by dividing by the scale and focusing
		spawnPoint.x = spawnPoint.x / (int)sc;
		spawnPoint.y = spawnPoint.y / (int)sc;
		Camera::Instance()->SetFocus(spawnPoint);
	}
	else
	{
		std::cout << "XML sheet could not be found: " << std::string(XMLPath) << std::endl;
	}
}

bool LevelManager::SaveLevel(std::string name)
{
	//Create document
	XMLDocument xmlDoc;

	//Set up an element to set attributes
	XMLElement* pRootElement = xmlDoc.NewElement("leveldata");
	pRootElement->SetAttribute("name", "testlevelname");
	pRootElement->SetAttribute("spawnx", 370);
	pRootElement->SetAttribute("spawny", 395);
	pRootElement->SetAttribute("mapx", 0);
	pRootElement->SetAttribute("mapy", 0);
	pRootElement->SetAttribute("mapw", 1500);
	pRootElement->SetAttribute("maph", 2000);
	pRootElement->SetAttribute("levelendx", 1024);
	pRootElement->SetAttribute("levelendy", 0);
	pRootElement->SetAttribute("levelendw", 1024);
	pRootElement->SetAttribute("levelendh", 768);
	pRootElement->SetAttribute("skyr", 255);
	pRootElement->SetAttribute("skyg", 255);
	pRootElement->SetAttribute("skyb", 255);
	pRootElement->SetAttribute("skya", 255);

	//Set up the root node
	XMLNode* pRoot = pRootElement;
	xmlDoc.InsertFirstChild(pRoot);
	

	//Cycle through tiles and write xml
	for (std::vector<GameTile*>::size_type i = 0; i != levelTiles.size(); i++)
	{
		if (i != NULL)
		{
			XMLElement* pElement = xmlDoc.NewElement("tile");
			pElement->SetAttribute("name", levelTiles[i]->GetTileName().c_str());
			pElement->SetAttribute("posX", levelTiles[i]->GetPoint().x);
			pElement->SetAttribute("posY", levelTiles[i]->GetPoint().y);
			pElement->SetAttribute("physics", levelTiles[i]->GetPhysics());
			pElement->SetAttribute("sound", levelTiles[i]->GetSound());
			pElement->SetAttribute("action", false);
			pRoot->InsertEndChild(pElement);
		}
	}

	//Save document
	xmlDoc.SaveFile(name.c_str());
	return true;
}

void LevelManager::CleanLevel()
{
	//Clear tiles and joints, save player coords
	for (std::vector<b2Joint*>::size_type i = 0; i != levelJoints.size(); i++)
	{
		world->DestroyJoint(levelJoints[i]);
	}

	for (std::vector<GameTile*>::size_type i = 0; i != levelTiles.size(); i++)
	{
		levelTiles[i]->Delete();
	}

	player.Freeze();

	levelTiles.clear();
	levelJoints.clear();

	player.UnFreeze();
}

LevelManager::~LevelManager()
{

}