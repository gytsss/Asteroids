#pragma once
#include "raylib.h"


struct Spaceman
{
	float x;
	float y;
	bool isGoingBack;
	bool isActive;
	int lifes;
	Vector2 position;
	Vector2 speed;
};

void initSpaceman(Spaceman& spaceman);

void drawSpaceman(Texture2D spacemanSprite, float frameWidth, float frameHeight, int frame);

void spacemanMovement();

void menuSpacemanMovement();