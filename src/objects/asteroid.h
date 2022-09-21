#pragma once
#include "raylib.h"
#include <iostream>

enum AsteroidSize
{
	Small,
	Medium,
	Big
};

struct Asteroid
{
	int x;
	int y;
	int radius;
	float rotation;
	Vector2 position;
	Vector2 speed;
	AsteroidSize size;
};

Asteroid initAsteroid(int x, int y, int radius, float rotation);
