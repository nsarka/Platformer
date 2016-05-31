#include "Player.h"
#include "Camera.h"
#include "GameSystem.h"
#include "Util.h"

Player::Player()
{
	playerSheet = new SpriteSheet("Assets/p1_spritesheet.xml");

	playerScreenPos.x = 1024 / 2;
	playerScreenPos.y = 768 / 2;

	for (int i = 0; i <= playerDriftFrameTotal; i++)
	{
		playerDriftX[i] = 0;
		playerDriftY[i] = 0;
	}

	playerDriftCounter = 0;

	objFrame = playerSheet->GetFrame("p1_stand");
}

void Player::SetSky(int skyr, int skyg, int skyb, int skya)
{
	skyColor.r = skyr;
	skyColor.g = skyg;
	skyColor.b = skyb;
	skyColor.a = skya;
}

void Player::Load(std::string path, std::string texture, int x, int y, SDL_Renderer* pRenderer, b2World* world)
{
	TextureManager::Instance()->LoadTexture(path, texture, pRenderer);

	textureID = texture;
	playerWorldPos.x = x;
	playerWorldPos.y = y;

	playerBodyDef.position.Set(x / sc, -y / sc);
	playerBodyDef.type = b2_dynamicBody;
	playerBody = world->CreateBody(&playerBodyDef);
	playerBody->SetFixedRotation(true);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((objFrame.w/2) / sc, (objFrame.h/2) / sc);

	// Define the dynamic body fixture.
	playerFixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	playerFixtureDef.density = 1.0f;

	// Override the default friction.
	playerFixtureDef.friction = 1.5f;

	//He shouldnt bounce, i dont know why he still does
	playerFixtureDef.restitution = 0.0f;

	// Add the shape to the body.
	b2Fixture* playerFixture = playerBody->CreateFixture(&playerFixtureDef);
	playerFixture->SetUserData((void*)6);

	//Create the foot sensor
	dynamicBox.SetAsBox(1, 0.1, b2Vec2(0, 0-(objFrame.h/2/sc)), 0);
	playerFixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = playerBody->CreateFixture(&playerFixtureDef);
	footSensorFixture->SetUserData((void*)3);
	
	//Create player sides to prevent friction
	playerFixtureDef.isSensor = false;
	playerFixtureDef.friction = 0.0f;
	dynamicBox.SetAsBox(0.01, (objFrame.h/2/sc)-0.1, b2Vec2(0+objFrame.w/2/sc, 0.1), 0);
	b2Fixture* playerSideRightFixture = playerBody->CreateFixture(&playerFixtureDef);

	//Left side
	dynamicBox.SetAsBox(0.01, (objFrame.h/2/sc)-0.1, b2Vec2(0-objFrame.w/2/sc, 0.1), 0);
	b2Fixture* playerSideLeftFixture = playerBody->CreateFixture(&playerFixtureDef);
}

void Player::drawBody(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	
	int ox = Camera::Instance()->GetOffsetDrift().x;
	int oy = Camera::Instance()->GetOffset().y;

	//http://box2d.org/forum/viewtopic.php?f=3&t=1933
	for (b2Fixture *fixture = playerBody->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		if (fixture->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape *poly = (b2PolygonShape*)fixture->GetShape();

			const int count = poly->GetVertexCount();

			for (int i = 0; i < count; i++)
			{
				int ind0 = (i + 1) % count;
				b2Vec2 p0 = playerBody->GetWorldPoint(poly->GetVertex(ind0));
				b2Vec2 p1 = playerBody->GetWorldPoint(poly->GetVertex(i));

				SDL_RenderDrawLine(renderer,
					sc * p0.x - ox, -sc * p0.y - oy,
					sc * p1.x - ox, -sc * p1.y - oy
					);
			}
			//verts now contains world co-ords of all the verts
		}
	}

	SDL_SetRenderDrawColor(renderer, skyColor.r, skyColor.g, skyColor.b, skyColor.a);
}

void Player::Update()
{
	//Let him move with input
	HandleInput();

	//Update him
	b2Vec2 point = playerBody->GetPosition();
	playerWorldPos.x = (point.x*sc) - (objFrame.w/2);
	playerWorldPos.y = (-point.y*sc) - (objFrame.h/2);

	//Change his screen position to show drift
	playerScreenPos.x = playerWorldPos.x - Camera::Instance()->GetOffsetDrift().x;
	playerScreenPos.y = playerWorldPos.y - Camera::Instance()->GetOffset().y;

	//Make him look like hes falling if his y velocity is fast
	if (!playerDuck)
	{
		if (playerBody->GetLinearVelocity().y > 3 || playerBody->GetLinearVelocity().y < -3)
		{
			objFrame = playerSheet->GetFrame("p1_jump");
		}
	}
	else
	{
		//change size to make him duck
	}

	//Set the drift to lag behind the player
	CalcAndSetDrift();

	//Let the camera follow him
	Camera::Instance()->SetFocus(playerWorldPos);
}

void Player::CalcAndSetDrift()
{
	//Set drift according to average velocity of last n frames to eliminate the jerk of the camera if you run into a wall
	if (playerDriftCounter >= playerDriftFrameTotal)
	{
		playerDriftCounter = 0;
	}
	else
	{
		playerDriftCounter++;
	}

	playerDriftX[playerDriftCounter] = playerBody->GetLinearVelocity().x * 20;
	playerDriftY[playerDriftCounter] = playerBody->GetLinearVelocity().y * 20;

	SDL_Point p;
	p.x = 0;
	p.y = 0;

	for (int i = 0; i <= playerDriftFrameTotal; i++)
	{
		p.x += playerDriftX[i];
		p.y += playerDriftY[i];
	}

	p.x /= playerDriftFrameTotal;
	p.y /= playerDriftFrameTotal;

	Camera::Instance()->SetDrift(p);
}

void Player::Draw(SDL_Renderer* pRenderer, bool debug)
{
	if (debug)
	{
		drawBody(pRenderer);
	}

	TextureManager::Instance()->DrawTexture(textureID,
		playerScreenPos.x,
		playerScreenPos.y,
		objFrame.w, objFrame.h, objFrame.x, objFrame.y,
		0, pRenderer,
		playerFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Player::HandleInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	int boundsCheckX = Camera::Instance()->IsOutOfMapBoundariesX(playerWorldPos.x);
	int boundsCheckY = Camera::Instance()->IsOutOfMapBoundariesY(playerWorldPos.y);

	if (!state[SDL_SCANCODE_RIGHT] || !state[SDL_SCANCODE_LEFT])
	{
		objFrame = playerSheet->GetFrame("p1_stand");
	}

	if (state[SDL_SCANCODE_DOWN])
	{
		playerDuck = true;
		
		objFrame = playerSheet->GetFrame("p1_duck");
		playerBody->ApplyLinearImpulse(b2Vec2(0.0, -1.0), b2Vec2(0.0, 0.0), true);
	}

	if (state[SDL_SCANCODE_UP])
	{
		if(numFootContacts > 0)
		{
			objFrame = playerSheet->GetFrame("p1_jump");
			playerBody->ApplyLinearImpulse(b2Vec2(0, 15.0), b2Vec2(0, 0), true);
		}
	}

	if (state[SDL_SCANCODE_LEFT])
	{
		playerFlip = true;
		objFrame = playerSheet->GetFrame(walkFrames[int(((SDL_GetTicks() / 25) % 11))]);

		if (playerBody->GetLinearVelocity().x > (playerSprint ? -7.0 : -5.0))
		{
			playerBody->ApplyLinearImpulse(b2Vec2(playerSprint ? -3 : -2, 0), b2Vec2(0, 0), true);
		}
	}

	if (state[SDL_SCANCODE_RIGHT])
	{
		playerFlip = false;
		objFrame = playerSheet->GetFrame(walkFrames[int(((SDL_GetTicks() / 25) % 11))]);

		if (playerBody->GetLinearVelocity().x < (playerSprint ? 7.0 : 5.0))
		{
			playerBody->ApplyLinearImpulse(b2Vec2(playerSprint ? 3 : 2, 0), b2Vec2(0, 0), true);
		}
	}

	if (state[SDL_SCANCODE_F5])
	{
		//Toggles need a second to cool down
		if (SDL_GetTicks() >= playerNextToggle)
		{
			ToggleFreeze();
			playerNextToggle += SDL_GetTicks() + 1000.0f;
		}
	}

	if (state[SDL_SCANCODE_LSHIFT])
	{
		//Toggle sprint
		playerSprint = true;
	}
	else if (!state[SDL_SCANCODE_LSHIFT])
	{
		playerSprint = false;
	}
}

void Player::ToggleFreeze()
{
	if (!playerFreeze)
	{
		playerFreeze = true;
		std::cout << "Frozen" << std::endl;
		Freeze();
	}
	else
	{
		playerFreeze = false;
		std::cout << "Unfrozen" << std::endl;
		UnFreeze();
	}
}

void Player::Freeze()
{
	playerBody->SetType(b2_staticBody);
}

void Player::UnFreeze()
{
	if(playerBody != 0)
	{
		playerBody->SetType(b2_dynamicBody);
	}
}