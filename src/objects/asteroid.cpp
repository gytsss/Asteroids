#include "asteroid.h"


Asteroid initAsteroid(int x, int y, int radius, float rotation)
{
	Asteroid asteroid = { x, y, radius, rotation };
	return asteroid;

}