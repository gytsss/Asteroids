#include "asteroid.h"

Asteroid bigAsteroid[maxBigAsteroids];
Asteroid mediumAsteroid[maxMediumAsteroids];
Asteroid smallAsteroid[maxSmallAsteroids];
Asteroid asteroids[maxAsteroids];

Asteroid initAsteroid(Asteroid& asteroid, int x, int y, float rotation, AsteroidSize size)
{
	asteroid = { x, y };
	asteroid.rotation = rotation;
	asteroid.size = size;

	if (asteroid.size == Small)
		asteroid.radius = 15;
	if (asteroid.size == Medium)
		asteroid.radius = 28;
	if (asteroid.size == Big)
		asteroid.radius = 40;


	/*int randomSpeedX;
	int randomSpeedY;

	do
	{
		randomSpeedX = GetRandomValue(-200, 200);

	} while (randomSpeedX > -70 && randomSpeedX < 70);

	do
	{
		randomSpeedY = GetRandomValue(-200, 200);

	} while (randomSpeedY >= -70 && randomSpeedY <= 70);*/


	/*asteroid.speed.x = randomSpeedX;
	asteroid.speed.y = randomSpeedY;*/

	asteroid.speed = { 0,0 };

	asteroid.isActive = true;
	return asteroid;
}

void drawAsteroid(Texture2D asteroidSprite, int i)
{
	
		if (asteroids[i].size == Big && asteroids[i].isActive)
		{
			DrawTexturePro(asteroidSprite,
				Rectangle{ 0, 0, (float)asteroidSprite.width ,(float)asteroidSprite.height },
				Rectangle{ (float)asteroids[i].x, (float)asteroids[i].y, 100, 100 },
				Vector2{ 100 / 2, 100 / 2 },
				asteroids[i].rotation,
				WHITE);
		}
		else if (asteroids[i].size == Medium && asteroids[i].isActive)
		{
			DrawTexturePro(asteroidSprite,
				Rectangle{ 0, 0, (float)asteroidSprite.width ,(float)asteroidSprite.height },
				Rectangle{ (float)asteroids[i].x, (float)asteroids[i].y, 53, 53 },
				Vector2{ 53 / 2, 53 / 2 },
				asteroids[i].rotation,
				WHITE);
		}
		else if (asteroids[i].size == Small && asteroids[i].isActive)
		{
			DrawTexturePro(asteroidSprite,
				Rectangle{ 0, 0, (float)asteroidSprite.width ,(float)asteroidSprite.height },
				Rectangle{ (float)asteroids[i].x, (float)asteroids[i].y, 30, 30 },
				Vector2{ 30 / 2, 30 / 2 },
				asteroids[i].rotation,
				WHITE);
		}
	
}