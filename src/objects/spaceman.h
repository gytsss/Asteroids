#pragma once
#include "raylib.h"


struct Spaceman
{
	float x;
	float y;
	bool isGoingBack;
	bool isActive;
	Vector2 position;
	Vector2 speed;
};

void initSpaceman(Spaceman& spaceman);