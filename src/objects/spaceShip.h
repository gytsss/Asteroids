#pragma once
#include "raylib.h"

#include "asteroid.h"
#include "spaceShip.h"


struct Ship
{
	float x;
	float y;
	int radius;
	int lifes;
	float rotation;
	bool isAlive;
	Vector2 position;
	Vector2 speed;
	Vector2 velocity;
};

Ship initShip();

void drawShip(Texture2D shipSprite, Texture2D shipSpriteNitro);

bool checkShipDead();



