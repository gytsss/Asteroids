#include "spaceman.h"

Spaceman spaceman;
Spaceman menuSpaceman;

void initSpaceman(Spaceman& spaceMan)
{
	spaceMan.x = 20;
	spaceMan.y = 47;
	spaceMan.position = { 10, 80 };
	spaceMan.lifes = 2;
	spaceMan.isGoingBack = false;
	spaceMan.isActive = true;

	spaceMan.speed.x = static_cast<float>(GetRandomValue(200, 400));
	
}

void drawSpaceman(Texture2D spacemanSprite, float frameWidth, float frameHeight, int frame)
{
	if (spaceman.isActive)
	{
		if (!spaceman.isGoingBack)
		{
			DrawTextureRec(spacemanSprite,
				Rectangle{ (frameWidth * frame) + 12, static_cast<float>(spacemanSprite.height / 3.25), frameWidth, frameHeight },
				spaceman.position,
				WHITE);
		}
		else if (spaceman.isGoingBack)
		{
			DrawTextureRec(spacemanSprite,
				Rectangle{ (frameWidth * frame) + 12 , static_cast<float>(spacemanSprite.height / 1.24), frameWidth, frameHeight },
				spaceman.position,
				WHITE);
		}
	}
}

void spacemanMovement()
{
	if (spaceman.isActive)
	{
		if (!spaceman.isGoingBack)
		{
			spaceman.position.x += spaceman.speed.x * GetFrameTime();
		}
		else if (spaceman.isGoingBack)
		{
			spaceman.position.x -= spaceman.speed.x * GetFrameTime();
		}
	}
}

void menuSpacemanMovement()
{
	if (!menuSpaceman.isGoingBack)
	{
		menuSpaceman.position.x += menuSpaceman.speed.x * GetFrameTime();
	}
	else if (menuSpaceman.isGoingBack)
	{
		menuSpaceman.position.x -= menuSpaceman.speed.x * GetFrameTime();
	}
}
