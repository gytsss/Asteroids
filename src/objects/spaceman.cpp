#include "spaceman.h"

Spaceman spaceman;

void initSpaceman(Spaceman& spaceMan)
{
	spaceMan.x = 10;
	spaceMan.y = 40;
	spaceMan.position = { 10, 80 };

	spaceMan.isGoingBack = false;
	spaceMan.isActive = true;

	spaceMan.speed.x = static_cast<float>(GetRandomValue(100, 200));
	spaceMan.speed.y = static_cast<float>(GetRandomValue(100, 200));
}