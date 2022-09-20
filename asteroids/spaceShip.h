#pragma once
#include "raylib.h"


struct Ship
{
	int x;
	int y;
	int radius;
	int lifes;
	float rotation;
	Vector2 position;
	Vector2 speed;
	
	
};

Ship initShip(Ship& ship);