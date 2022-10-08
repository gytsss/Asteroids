#include "bullets.h"
#include "spaceShip.h"
#include "raymath.h"

Bullet bullets[maxBullets];

Bullet initBullet(Bullet bullet, Ship ship, Vector2 vectorDirection)
{
	bullet.radius = 5;
	bullet.x = ship.position.x;
	bullet.y = ship.position.y;
	bullet.rotation = ship.rotation;
	bullet.isActive = true;

	Vector2 normalizeDirect = Vector2Normalize(vectorDirection);


	bullet.speed.x = normalizeDirect.x;
	bullet.speed.y = normalizeDirect.y;


	return bullet;

}