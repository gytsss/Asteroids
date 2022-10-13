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
	Credits,
	Quit
};

void runGame();

void input( Vector2 normalizeDirect);

void teleportationBox(Texture2D shipSprite, Texture2D asteroidSprite);

void drawCursor(Texture2D cursor, Vector2 mousePosition);

void menuBoxes(int& currentScreen, Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton);

void drawMenu(Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton, Font titleFont);

void creditBoxes(int& currentScreen, Texture2D creditButtons, Texture2D smallCreditButtons);

void drawCredits(Font font, Texture2D creditButtons, Texture2D smallCreditButtons);

void optionsBoxes(int &currentScreen, Texture2D smallCreditButtons);

void drawOptions(Texture2D smallCreditButtons, Font font, Font titleFont, Texture2D leftClick, Texture2D rightClick);

void options2Boxes(int& currentScreen, Texture2D smallCreditButtons);

void drawOptions2(Texture2D smallCreditButtons, Font font, Font titleFont, Font gameFont, Texture2D spacemanSpriteFront, Texture2D asteroidSprite);

void drawGame( Texture2D shipSprite, Texture2D asteroidSprite, Texture2D smallPauseButton, float score, Texture2D shipSpriteNitro, Font titleFont, Texture2D spacemanSprite, float frameWidth, float frameHeight, int frame, Texture2D bullet);

bool collisionCircleCircle(Vector2 center1, float radius1, Vector2 center2, float radius2);

void pauseMode(Texture2D playButton, Texture2D quitButton, Vector2 mousePosition, bool& pause, bool& firstLife, int& currentScreen, int& playOnce, float& score);