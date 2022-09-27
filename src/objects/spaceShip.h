#pragma once
#include "raylib.h"
#include "asteroid.h"
#include "spaceShip.h"


struct Ship
{
	int x;
	int y;
	int radius;
	int lifes;
	float rotation;
	bool isAlive;
	Vector2 position;
	Vector2 speed;
};

Ship initShip(Ship& ship);

void drawShip(Texture2D shipSprite, Texture2D shipSpriteNitro);

bool checkShipDead();



