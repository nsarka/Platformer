/*
	Thanks Erin Catto
*/

#include "Box2d.h"
#include "Util.h"

class ContactListener : public b2ContactListener
{
public:
	ContactListener(int& contacts) : FootContacts(contacts)
	{
		FootContacts = contacts;
	}

private:

	int& FootContacts;

	void BeginContact(b2Contact* contact)
	{
		//Check the fixture to see what it was
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();

		if ((int)fixtureUserData == 3) //Player feet
		{
			FootContacts++;
		}
		else if ((int)fixtureUserData == 6) //Player
		{
			
		}
		else if ((int)fixtureUserData == 8) //Tile
		{
			
		}

		//Check the fixture to see what it was
		fixtureUserData = contact->GetFixtureB()->GetUserData();

		if ((int)fixtureUserData == 3) //Player feet
		{
			FootContacts++;
		}
		else if ((int)fixtureUserData == 6) //Player body
		{
			
		}
		else if ((int)fixtureUserData == 8) //Tile
		{
			
		}
	}

	void EndContact(b2Contact* contact)
	{
		//Check the fixture to see what it was
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();

		if ((int)fixtureUserData == 3) //Player feet
		{
			FootContacts--;
		}
		else if ((int)fixtureUserData == 6) //Player body
		{

		}
		else if ((int)fixtureUserData == 8) // Tile
		{

		}

		//Check the fixture to see what it was
		fixtureUserData = contact->GetFixtureB()->GetUserData();

		if ((int)fixtureUserData == 3) //Player feet
		{
			FootContacts--;
		}
		else if ((int)fixtureUserData == 6) //Player body
		{
			
		}
		else if ((int)fixtureUserData == 8) //Tile
		{
			
		}
	}
};