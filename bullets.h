#pragma once
#include "raylib.h"

const int maxBullets = 15;

struct Bullet
{
	int x;
	int y;
	float radius;
	Vector2 speed;
};

Bullet initBullet(Bullet &bullet);