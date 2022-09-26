#pragma once
#include "raylib.h"
#include <iostream>

const int maxBigAsteroids = 1;
const int maxMediumAsteroids = 1;
const int maxSmallAsteroids = 1;

const int maxAsteroids = maxBigAsteroids + maxMediumAsteroids + maxSmallAsteroids;


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
	bool isActive;
	Vector2 position;
	Vector2 speed;
	AsteroidSize size;
};

Asteroid initAsteroid(Asteroid &asteroid,int x, int y, float rotation, AsteroidSize size);

void drawAsteroid( Texture2D asteroidSprite, int i);
