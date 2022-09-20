#include "spaceShip.h"
#include "raylib.h"

Ship initShip(Ship &ship)
{

	ship.x = 5;
	ship.y = 5;
	ship.radius = 25;
	ship.lifes = 3;
	ship.position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	ship.speed = { 0,0 };
	return ship;
}