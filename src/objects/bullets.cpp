#include "bullets.h"

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

void drawBullets(Texture2D bullet)
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (bullets[i].isActive)
		{
			DrawTexturePro(bullet,
				Rectangle{ 0, 0, static_cast<float>(bullet.width) ,static_cast<float>(bullet.height) },
				Rectangle{ static_cast<float>(bullets[i].x) , static_cast<float>(bullets[i].y), 70, 70 },
				Vector2{ 70 / 2, 70 / 2 },
				bullets[i].rotation,
				WHITE);
		}
	}
}