#include "bullets.h"
#include "spaceShip.h"

Bullet bullets[maxBullets];

Bullet initBullet(Bullet& bullet, Ship ship, Vector2 vectorDirection)
{
	bullet.radius = 5;
	bullet.x = ship.position.x;
	bullet.y = ship.position.y;
	bullet.rotation = ship.rotation;

	float vectorModule = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));
	Vector2 normalizeDirect = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

	bullet.speed.x = vectorDirection.x;
	bullet.speed.y = vectorDirection.y;

	return bullet;

}