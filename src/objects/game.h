#pragma once
#include "raylib.h"
#include "spaceShip.h"
#include "asteroid.h"

void runGame();

void input(Ship &ship, Vector2 &normalizeDirect);

void teleportationBox(Ship& ship, Texture2D shipSprite, Asteroid &asteroid, Texture2D asteroidSprite);

void drawCursor(Texture2D cursor, Vector2 mousePosition);

