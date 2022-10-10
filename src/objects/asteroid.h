#pragma once
#include "raylib.h"
#include <iostream>

const int maxBigAsteroids = 1;
const int maxMediumAsteroids = 1;
const int maxSmallAsteroids = 1;
const int maxAuxAsteroids = 20;

const int maxAsteroids = maxBigAsteroids + maxMediumAsteroids + maxSmallAsteroids + maxAuxAsteroids;


enum class AsteroidSize
{
	Small,
	Medium,
	Big
};

struct Asteroid
{
	float x;
	float y;
	int radius;
	float rotation;
	bool isActive;
	Vector2 position;
	Vector2 speed;
	AsteroidSize size;
};

void initAsteroid(Asteroid& asteroid,float x, float y, float rotation, AsteroidSize size);

void drawAsteroid( Texture2D asteroidSprite, int i);
