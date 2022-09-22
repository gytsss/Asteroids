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
	Credits,
	Quit
};

void runGame();

void input(Ship &ship, Vector2 &normalizeDirect);

void teleportationBox(Ship& ship, Texture2D shipSprite, Asteroid bigAsteroid[], Texture2D asteroidSprite);

void drawCursor(Texture2D cursor, Vector2 mousePosition);

void menuBoxes(int& currentScreen, Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton);

void drawMenu(Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton);

void creditBoxes(int& currentScreen, Texture2D creditButtons, Texture2D smallCreditButtons);

void drawCredits(Font font, Texture2D creditButtons, Texture2D smallCreditButtons);

void drawGame(Ship ship, Asteroid bigAsteroid[10], Texture2D shipSprite, Texture2D asteroidSprite, Texture2D smallPauseButton);
