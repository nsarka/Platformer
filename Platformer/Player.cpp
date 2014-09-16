#include "Player.h"
#include "Camera.h"
#include "GameSystem.h"
#include "Util.h"

Player::Player()
{
	playerSheet = new SpriteSheet("Assets/p2_spritesheet.xml");

	playerScreenPos.x = 1024 / 2;
	playerScreenPos.y = 768 / 2;

	objFrame = playerSheet->GetFrame("p2_stand");
}

void Player::Load(std::string path, std::string texture, int x, int y, SDL_Renderer* pRenderer, b2World* world)
{
	TextureManager::Instance()->LoadTexture(path, texture, pRenderer);

	textureID = texture;
	playerWorldPos.x = x;
	playerWorldPos.y = y;

	playerBodyDef.position.Set(x/sc, y/sc);
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
	playerFixtureDef.friction = 0.3f;

	//Bounce?
	playerFixtureDef.restitution = 0.1f;

	// Add the shape to the body.
	playerBody->CreateFixture(&playerFixtureDef);
}

void Player::drawBody(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	
	int ox = Camera::Instance()->GetOffset().x;
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

	SDL_SetRenderDrawColor(renderer, 208, 244, 247, 255);
}

void Player::Update()
{
	//Let him move with input
	HandleInput();

	//Update him
	b2Vec2 point = playerBody->GetPosition();
	playerWorldPos.x = (point.x*sc) - (objFrame.w/2);
	playerWorldPos.y = (-point.y*sc) - (objFrame.h / 2);

	//Let the camera follow him
	Camera::Instance()->SetFocus(playerWorldPos);
}

void Player::Draw(SDL_Renderer* pRenderer, bool debug)
{
	if (debug)
	{
		drawBody(pRenderer);
	}

	TextureManager::Instance()->DrawTexture(textureID, playerScreenPos.x, playerScreenPos.y, objFrame.w, objFrame.h, objFrame.x, objFrame.y, 0, pRenderer, playerFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Player::HandleInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	int boundsCheckX = Camera::Instance()->IsOutOfMapBoundariesX(playerWorldPos.x);
	int boundsCheckY = Camera::Instance()->IsOutOfMapBoundariesY(playerWorldPos.y);

	if (!state[SDL_SCANCODE_RIGHT] || !state[SDL_SCANCODE_LEFT])
	{
		objFrame = playerSheet->GetFrame("p2_stand");
	}

	if (state[SDL_SCANCODE_DOWN])
	{
		objFrame = playerSheet->GetFrame("p2_duck");
		playerBody->ApplyLinearImpulse(b2Vec2(0, -10), b2Vec2(0, 0), true);
	}

	if (state[SDL_SCANCODE_UP])
	{
		objFrame = playerSheet->GetFrame("p2_jump");
		playerBody->ApplyLinearImpulse(b2Vec2(0, 10), b2Vec2(0, 0), true);
	}

	if (state[SDL_SCANCODE_LEFT])
	{
		playerFlip = true;
		objFrame = playerSheet->GetFrame(walkFrames[int(((SDL_GetTicks() / 25) % 11))]);
		playerBody->ApplyLinearImpulse(b2Vec2(-10, 0), b2Vec2(0, 0), true);
	}

	if (state[SDL_SCANCODE_RIGHT])
	{
		playerFlip = false;
		objFrame = playerSheet->GetFrame(walkFrames[int(((SDL_GetTicks() / 25) % 11))]);
		playerBody->ApplyLinearImpulse(b2Vec2(10, 0), b2Vec2(0, 0), true);
	}
}