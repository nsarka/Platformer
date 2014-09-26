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
		//check if fixture A was the foot sensor
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();

		if ((int)fixtureUserData == 3)
		{
			FootContacts++;
		}

		//check if fixture B was the foot sensor
		fixtureUserData = contact->GetFixtureB()->GetUserData();

		if ((int)fixtureUserData == 3)
		{
			FootContacts++;
		}
	}

	void EndContact(b2Contact* contact)
	{
		//check if fixture A was the foot sensor
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();

		if ((int)fixtureUserData == 3)
		{
			FootContacts--;
		}

		//check if fixture B was the foot sensor
		fixtureUserData = contact->GetFixtureB()->GetUserData();

		if ((int)fixtureUserData == 3)
		{
			FootContacts--;
		}
	}
};