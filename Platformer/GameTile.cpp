#include "GameTile.h"
#include "Camera.h"
#include "Util.h"


GameTile::GameTile()
{

}

/* Thank you Erin Catto */
void GameTile::drawBody(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	int ox = Camera::Instance()->GetOffsetDrift().x;
	int oy = Camera::Instance()->GetOffset().y;

	//http://box2d.org/forum/viewtopic.php?f=3&t=1933
	for (b2Fixture *fixture = tileBody->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		if (fixture->GetType() == b2Shape::e_polygon)
		{
			b2PolygonShape *poly = (b2PolygonShape*)fixture->GetShape();

			const int count = poly->GetVertexCount();

			for (int i = 0; i < count; i++)
			{
				int ind0 = (i + 1) % count;
				b2Vec2 p0 = tileBody->GetWorldPoint(poly->GetVertex(ind0));
				b2Vec2 p1 = tileBody->GetWorldPoint(poly->GetVertex(i));

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

void GameTile::Draw(SDL_Renderer* pRenderer, bool tileDebug)
{
	if (IsTileInScreen(point.x - Camera::Instance()->GetOffsetDrift().x, point.y - Camera::Instance()->GetOffset().y, frame.w, frame.h))
	{
		//Get the angle of the body, convert to degrees, and draw
		if (physics != 0)
		{
			angle = tileBody->GetAngle()*-RADTODEG; //negative because its backwards
		}
		else
		{
			angle = 0;
		}
		
		//Subtract camera offset so the tiles scroll
		TextureManager::Instance()->DrawTexture(ImageName, point.x - Camera::Instance()->GetOffsetDrift().x, point.y - Camera::Instance()->GetOffset().y, frame.w, frame.h, frame.x, frame.y, angle, pRenderer, SDL_FLIP_NONE);
	}

	if (tileDebug == true && physics != 0)
	{
		drawBody(pRenderer);
	}
}


void GameTile::Update()
{
	if (tileBody != 0)
	{
		b2Vec2 pos = tileBody->GetPosition();

		point.x = (pos.x*sc)-(frame.w/2);
		point.y = (-pos.y*sc)-(frame.h/2);
	}
}


bool GameTile::IsTileInScreen(int x, int y, int w, int h)
{
	//x + w because we want to check to the right corners, not the left
	if(x + w <= 0)
	{
		return false;
	}

	//Same thing for y but for height
	if (y + h <= 0)
	{
		return false;
	}

	if (x >= 1024)
	{
		return false;
	}

	if (y >= 768)
	{
		return false;
	}

	return true;
}

void GameTile::SetFrame(SDL_Rect Frame)
{
	frame = Frame;
}

void GameTile::SetImageName(std::string TextureName)
{
	ImageName = TextureName;
}

void GameTile::SetTileName(std::string TileName)
{
	TileName = TileName;
}

void GameTile::SetPoint(SDL_Point Point)
{
	point = Point;
}

b2Body* GameTile::SetPhysics(int Physics, b2World* world)
{
	physics = Physics;

	if (physics != 0)
	{
		// Define the dynamic body. We set its position and call the body factory.
		switch (physics)
		{
		case 1: tileBodyDef.type = b2_staticBody; break;
		case 2: tileBodyDef.type = b2_dynamicBody; break;
		case 3: tileBodyDef.type = b2_kinematicBody; break;
		}

		tileBodyDef.position.Set((point.x-(frame.w/2)) / sc, (-point.y-(frame.h/2)) / sc);
		tileBody = world->CreateBody(&tileBodyDef);

		// Define another box shape for our dynamic body.
		b2PolygonShape Box;
		Box.SetAsBox((frame.w/2) / sc, (frame.h/2) / sc);

		// Define the dynamic body fixture.
		tileFixtureDef.shape = &Box;

		// Set the box density to be non-zero, so it will be dynamic.
		tileFixtureDef.density = 1.0f;

		// Override the default friction.
		tileFixtureDef.friction = 0.3f;

		// Make it bouncy for debug
		tileFixtureDef.restitution = 0.1f;

		// Add the shape to the body.
		b2Fixture* tileFixture = tileBody->CreateFixture(&tileFixtureDef);
		tileFixture->SetUserData((void*)8);

		return tileBody;
	}

	return 0;
}

void GameTile::SetSound(int Sound)
{
	sound = Sound;
}

void GameTile::SetAction(bool Action)
{
	action = Action;
}

void GameTile::Delete()
{
	if (tileBody)
	{
		tileBody->GetWorld()->DestroyBody(tileBody);
	}
}

GameTile::~GameTile()
{

}
