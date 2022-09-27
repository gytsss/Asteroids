#pragma once
#include "raylib.h"
#include "spaceShip.h"

const int maxBullets = 15;

struct Bullet
{
	float x;
	float y;
	float radius;
	float rotation;
	bool isActive;
	Vector2 speed;
};

Bullet initBullet(Bullet& bullet, Ship ship, Vector2 vectorDirection);


