#include "asteroid.h"

Asteroid initAsteroid(int x, int y, int radius, float rotation)
{
	Asteroid asteroid = { x, y, radius, rotation };
	return asteroid;

}

void drawAsteroid(Asteroid &asteroid, Texture2D asteroidSprite)
{
	DrawTexturePro(asteroidSprite,
		Rectangle{ 0, 0, (float)asteroidSprite.width ,(float)asteroidSprite.height },
		Rectangle{ (float)asteroid.x, (float)asteroid.y, 50, 50 },
		Vector2{ 50 / 2, 50 / 2 },
		asteroid.rotation,
		WHITE);
}