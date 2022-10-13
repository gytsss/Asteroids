#pragma once
#include "raylib.h"

#include "spaceShip.h"
#include "asteroid.h"

const Color AQUA = Color{ 95, 255, 253, 255 };

enum Screen
{
	Menu,
	Game,
	Options,
	Options2,
	Options3,
	Credits,
	Quit
};

void runGame();




