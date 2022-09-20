#include <iostream>
#include "math.h"
#include "game.h"
#include "spaceShip.h"


Ship ship;

void runGame()
{
	HideCursor();

	initShip(ship);

	Texture2D shipSprite = LoadTexture("res/bluespaceship.png");

	Vector2 mousePosition;

	float vectorModule;
	Vector2 normalizeDirect;

	Color colorCircle = WHITE;

	while (!WindowShouldClose())
	{
		mousePosition = GetMousePosition();

		Vector2 vectorDirection = { mousePosition.x - ship.position.x,  mousePosition.y - ship.position.y };

		float arcTan = atan2(vectorDirection.y, vectorDirection.x);
		float angle = arcTan * 180 / PI;

		ship.rotation = angle;

		vectorModule = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));

		normalizeDirect = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

		//input
		input(ship, normalizeDirect);


		if (ship.position.x > GetScreenWidth() + shipSprite.width)
			ship.position.x = 0;
		if (ship.position.x < 0 - shipSprite.width)
			ship.position.x = GetScreenWidth() + 4;

		if (ship.position.y > GetScreenHeight() + shipSprite.height)
			ship.position.y = 0;
		if (ship.position.y < 0 - shipSprite.height)
			ship.position.y = GetScreenHeight() + 4;


		if (CheckCollisionPointCircle(mousePosition, Vector2{ ship.position.x , ship.position.y }, ship.radius))
		{
			colorCircle = RED;
		}
		else
			colorCircle = WHITE;

		BeginDrawing();
		ClearBackground(BLACK);


		DrawCircleLines(ship.position.x, ship.position.y, ship.radius, colorCircle);

		DrawLineEx(ship.position, mousePosition, 1, WHITE);
		DrawFPS(10, 10);


		DrawTexturePro(shipSprite,
			Rectangle{ 0, 0, (float)shipSprite.width,(float)shipSprite.height },
			Rectangle{ ship.position.x, ship.position.y, 50, 50 },
			Vector2{ (float)shipSprite.width / 2,(float)shipSprite.height / 2 },
			ship.rotation,
			WHITE);


		DrawPixelV(mousePosition, RED);

		EndDrawing();
	}

	UnloadTexture(shipSprite);
}


void input(Ship& ship, Vector2& normalizeDirect)
{
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		ship.speed.x += normalizeDirect.x;
		ship.speed.y += normalizeDirect.y;
	}

	ship.position.x += ship.speed.x * GetFrameTime() * 5;
	ship.position.y += ship.speed.y * GetFrameTime() * 5;
}

