#include "spaceman.h"

Spaceman spaceman;

void initSpaceman(Spaceman& spaceman)
{
	spaceman.x = 10;
	spaceman.y = 40;

	spaceman.isgoingBack = false;
	spaceman.isActive = true;
	spaceman.position = { 10, 50 };

	int randomSpeedX;
	int randomSpeedY;

	do
	{
		randomSpeedX = GetRandomValue(-200, 200);

	} while (randomSpeedX > -70 && randomSpeedX < 70);

	do
	{
		randomSpeedY = GetRandomValue(-200, 200);

	} while (randomSpeedY >= -70 && randomSpeedY <= 70);


	spaceman.speed.x = static_cast<float>(randomSpeedX);
	spaceman.speed.y = static_cast<float>(randomSpeedY);
	
}