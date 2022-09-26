#include "bullets.h"


Bullet bullets[maxBullets];

Bullet initBullet(Bullet &bullet, Ship ship)
{
	bullet.radius = 4;
	bullet.x = ship.x;
	bullet.y = ship.y;



	return bullet;
}