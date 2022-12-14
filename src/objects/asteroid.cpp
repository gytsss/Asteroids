#include "asteroid.h"

Asteroid bigAsteroids[maxBigAsteroids];
Asteroid mediumAsteroids[maxMediumAsteroids];
Asteroid smallAsteroids[maxSmallAsteroids];
Asteroid auxAsteroids[maxAuxAsteroids];
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

	asteroid.rotationVel = 100;

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
			Rectangle{ 0, 0, static_cast<float>(asteroidSprite.width) ,static_cast<float>(asteroidSprite.height) },
			Rectangle{ static_cast<float>(asteroids[i].x), static_cast<float>(asteroids[i].y), 30, 30 },
			Vector2{ 30 / 2, 30 / 2 },
			asteroids[i].rotation,
			WHITE);
	}

}

void separateAsteroids(int i)
{
	if (asteroids[i].size == AsteroidSize::Big)
	{
		initAsteroid(asteroids[i], asteroids[i].x, asteroids[i].y, 0, AsteroidSize::Medium);

		int count = 0;
		for (int k = maxAsteroids - 1; k >= 0; k--)
		{
			if (!asteroids[k].isActive && count == 0)
			{
				initAsteroid(asteroids[k], asteroids[i].x, asteroids[i].y, 0, AsteroidSize::Medium);

				count++;
			}
		}

	}
	else if (asteroids[i].size == AsteroidSize::Medium)
	{
		initAsteroid(asteroids[i], asteroids[i].x, asteroids[i].y, 0, AsteroidSize::Small);
		int count = 0;
		for (int k = maxAsteroids - 1; k >= 0; k--)
		{
			if (!asteroids[k].isActive && count == 0)
			{
				initAsteroid(asteroids[k], asteroids[i].x, asteroids[i].y, 0, AsteroidSize::Small);

				count++;
			}
		}
	}
}

bool anyAsteroidAlive()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		if (asteroids[i].isActive)
		{
			return false;
		}
	}

	return true;
}

void organizeAsteroids(int& countAsteroids)
{

	for (int i = 0; i < maxBigAsteroids; i++)
	{
		asteroids[countAsteroids] = bigAsteroids[i];
		countAsteroids++;

	}
	for (int i = 0; i < maxMediumAsteroids; i++)
	{
		asteroids[countAsteroids] = mediumAsteroids[i];
		countAsteroids++;
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		asteroids[countAsteroids] = smallAsteroids[i];
		countAsteroids++;
	}
	for (int i = 0; i < maxAuxAsteroids; i++)
	{
		asteroids[countAsteroids] = auxAsteroids[i];
		countAsteroids++;

	}
}

void asteroidsMovement()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		asteroids[i].x += asteroids[i].speed.x * GetFrameTime();
		asteroids[i].y += asteroids[i].speed.y * GetFrameTime();
		asteroids[i].rotation += 1 * asteroids[i].rotationVel *  GetFrameTime();
	}
}

void initAllAsteroids()
{
	for (int i = 0; i < maxBigAsteroids; i++)
	{
		initAsteroid(bigAsteroids[i], static_cast<float>(GetRandomValue(10, 500)), static_cast<float>(GetRandomValue(10, 500)), 0, AsteroidSize::Big);
	}
	for (int i = 0; i < maxMediumAsteroids; i++)
	{
		initAsteroid(mediumAsteroids[i], static_cast<float>(GetRandomValue(10, 500)), static_cast<float>(GetRandomValue(10, 500)), 0, AsteroidSize::Medium);
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		initAsteroid(smallAsteroids[i], static_cast<float>(GetRandomValue(10, 500)), static_cast<float>(GetRandomValue(10, 500)), 0, AsteroidSize::Small);
	}
	for (int i = 0; i < maxAuxAsteroids; i++)
	{
		auxAsteroids[i].isActive = false;

	}
}