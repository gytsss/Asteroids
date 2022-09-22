#include "asteroid.h"

Asteroid bigAsteroid[10];

Asteroid initAsteroid(Asteroid &asteroid, int x, int y, int radius, float rotation)
{
	asteroid = { x, y, radius, rotation };
	asteroid.speed = { (float)GetRandomValue(70, 200), (float)GetRandomValue(70, 200) };

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


	asteroid.speed.x = randomSpeedX;
	asteroid.speed.y = randomSpeedY;

	return asteroid;
}

void drawAsteroid( Texture2D asteroidSprite, int i)
{
	DrawTexturePro(asteroidSprite,
		Rectangle{ 0, 0, (float)asteroidSprite.width ,(float)asteroidSprite.height },
		Rectangle{ (float)bigAsteroid[i].x, (float)bigAsteroid[i].y, 50, 50 },
		Vector2{ 50 / 2, 50 / 2 },
		bigAsteroid[i].rotation,
		WHITE);
}