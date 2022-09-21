#include "spaceShip.h"
#include "raylib.h"

Ship ship;

Ship initShip(Ship &ship)
{

	ship.x = 5;
	ship.y = 5;
	ship.radius = 23;
	ship.lifes = 3;
	ship.position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	ship.speed = { 0,0 };
	return ship;
}

void drawShip(Texture2D shipSprite)
{
	DrawTexturePro(shipSprite,
		Rectangle{ 0, 0, (float)shipSprite.width,(float)shipSprite.height },
		Rectangle{ ship.position.x, ship.position.y, (float)shipSprite.width, (float)shipSprite.height },
		Vector2{ (float)shipSprite.width / 2,(float)shipSprite.height / 2 },
		ship.rotation,
		WHITE);
}