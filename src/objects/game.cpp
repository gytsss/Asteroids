#include <iostream>
#include "math.h"
#include "game.h"
#include "spaceShip.h"
#include "asteroid.h"


extern Ship ship;

void runGame()
{
	HideCursor();

	initShip(ship);

	Texture2D shipSprite = LoadTexture("res/bluespaceship.png");
	Texture2D cursor = LoadTexture("res/cursor.png");
	Texture2D asteroidSprite = LoadTexture("res/asteroid.png");

	Vector2 mousePosition;

	float vectorModule;
	Vector2 normalizeDirect;

	Color colorCircle = WHITE;

	Asteroid asteroid = initAsteroid(GetRandomValue(10, 500), GetRandomValue(10, 500), 25, 0);


	int timer = 0;

	asteroid.speed = { (float)GetRandomValue(20, 200), (float)GetRandomValue(20, 200) };

	while (!WindowShouldClose())
	{

		mousePosition = GetMousePosition();

		Vector2 vectorDirection = { mousePosition.x - ship.position.x,  mousePosition.y - ship.position.y };

		float arcTan = atan2(vectorDirection.y, vectorDirection.x);
		float angle = arcTan * 180 / PI;

		ship.rotation = angle;

		vectorModule = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));

		normalizeDirect = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

		input(ship, normalizeDirect);

		teleportationBox(ship, shipSprite, asteroid, asteroidSprite);


		asteroid.x += asteroid.speed.x * GetFrameTime();
		asteroid.y += asteroid.speed.y * GetFrameTime();


		if (CheckCollisionCircles(Vector2{ (float)asteroid.x , (float)asteroid.y }, asteroid.radius, Vector2{ ship.position.x , ship.position.y }, ship.radius))
		{
			colorCircle = RED;
			ship.lifes--;
			ship.speed = { 0,0 };
			ship.position.x = GetScreenWidth() / 2;
			ship.position.y = GetScreenHeight() / 2;
		}
		else
			colorCircle = WHITE;




		BeginDrawing();
		ClearBackground(BLACK);

		DrawCircleLines(ship.position.x, ship.position.y, ship.radius, colorCircle);

		drawShip(shipSprite);

		DrawCircleLines(asteroid.x, asteroid.y, asteroid.radius, WHITE);


		DrawTexturePro(asteroidSprite,
			Rectangle{ 0, 0, (float)asteroidSprite.width ,(float)asteroidSprite.height },
			Rectangle{ (float)asteroid.x, (float)asteroid.y, 50, 50 },
			Vector2{ 50 / 2, 50 / 2 },
			asteroid.rotation,
			WHITE);

		DrawText(TextFormat("Lifes: %i", ship.lifes), GetScreenWidth() / 2 - 20, 10, 40, RED);


		drawCursor(cursor, mousePosition);
		DrawFPS(10, 10);
		EndDrawing();
	}

	UnloadTexture(shipSprite);
	UnloadTexture(cursor);
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

void teleportationBox(Ship& ship, Texture2D shipSprite, Asteroid& asteroid, Texture2D asteroidSprite)
{
	if (ship.position.x > GetScreenWidth() + shipSprite.width - 5)
		ship.position.x = -4;
	if (ship.position.x < 0 - shipSprite.width + 5)
		ship.position.x = GetScreenWidth() + 4;

	if (ship.position.y > GetScreenHeight() + shipSprite.height - 5)
		ship.position.y = -4;
	if (ship.position.y < 0 - shipSprite.height + 5)
		ship.position.y = GetScreenHeight() + 4;

	if (asteroid.x > GetScreenWidth() + shipSprite.width / 2)
		asteroid.x = 0;
	if (asteroid.x < 0 - shipSprite.width / 2)
		asteroid.x = GetScreenWidth();

	if (asteroid.y > GetScreenHeight() + shipSprite.height / 2)
		asteroid.y = 0;
	if (asteroid.y < 0 - shipSprite.height / 2)
		asteroid.y = GetScreenHeight();

}

void drawCursor(Texture2D cursor, Vector2 mousePosition)
{
	DrawTexturePro(cursor,
		Rectangle{ 0, 0, (float)cursor.width,(float)cursor.height },
		Rectangle{ mousePosition.x, mousePosition.y, 30, 30 },
		Vector2{ (float)cursor.width / 2 + 5,(float)cursor.height / 2 + 5 },
		0,
		WHITE);
}

