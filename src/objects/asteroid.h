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

Asteroid initAsteroid(Asteroid &asteroid,int x, int y, int radius, float rotation);

void drawAsteroid( Texture2D asteroidSprite, int i);
