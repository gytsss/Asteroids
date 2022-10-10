#include "asteroid.h"

Asteroid bigAsteroid[maxBigAsteroids];
Asteroid mediumAsteroid[maxMediumAsteroids];
Asteroid smallAsteroid[maxSmallAsteroids];
Asteroid auxAsteroid[maxAuxAsteroids];
Asteroid asteroids[maxAsteroids];

void initAsteroid(Asteroid& asteroid, float x, float y, float rotation, AsteroidSize size)
{
	asteroid = { x, y };
	asteroid.rotation = rotation;
	asteroid.size = size;

	if (asteroid.size == AsteroidSize::Small)
		asteroid.radius = 15;
	if (asteroid.size == AsteroidSize::Medium)
		asteroid.radius = 28;
	if (asteroid.size == AsteroidSize::Big)
		asteroid.radius = 40;


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


	asteroid.speed.x = static_cast<float>(randomSpeedX);
	asteroid.speed.y = static_cast<float>(randomSpeedY);

	asteroid.isActive = true;
}

void drawAsteroid(Texture2D asteroidSprite, int i)
{
	
		if (asteroids[i].size == AsteroidSize::Big && asteroids[i].isActive)
		{
			DrawTexturePro(asteroidSprite,
				Rectangle{ 0, 0, static_cast<float>(asteroidSprite.width) ,static_cast<float>(asteroidSprite.height) },
				Rectangle{ static_cast<float>(asteroids[i].x), static_cast<float>(asteroids[i].y), 100, 100 },
				Vector2{ 100 / 2, 100 / 2 },
				asteroids[i].rotation,
				WHITE);
		}
		else if (asteroids[i].size == AsteroidSize::Medium && asteroids[i].isActive)
		{
			DrawTexturePro(asteroidSprite,
				Rectangle{ 0, 0, static_cast<float>(asteroidSprite.width) ,static_cast<float>(asteroidSprite.height) },
				Rectangle{ static_cast<float>(asteroids[i].x), static_cast<float>(asteroids[i].y), 53, 53 },
				Vector2{ 53 / 2, 53 / 2 },
				asteroids[i].rotation,
				WHITE);
		}
		else if (asteroids[i].size == AsteroidSize::Small && asteroids[i].isActive)
		{
			DrawTexturePro(asteroidSprite,
				Rectangle{ 0, 0, static_cast<float>(asteroidSprite.width) ,static_cast<float>(asteroidSprite.height )},
				Rectangle{ static_cast<float>(asteroids[i].x), static_cast<float>(asteroids[i].y), 30, 30 },
				Vector2{ 30 / 2, 30 / 2 },
				asteroids[i].rotation,
				WHITE);
		}
	
}

void separateAsteroids()
{

}