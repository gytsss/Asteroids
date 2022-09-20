#include <iostream>
#include "raylib.h"
#include "math.h"
#include "spaceShip.h"
#include "game.h"


using namespace std;

Ship ship;

int main()
{
	float screenWidht = 1024;
	float screenHeight = 768;

	InitWindow(screenWidht, screenHeight, "Asteroids");
	SetWindowState(FLAG_VSYNC_HINT);
	HideCursor();

	initShip(ship);

	Texture2D shipSprite = LoadTexture("assets/bluespaceship.png");

	Vector2 mousePosition;

	Vector2 pivot = { 25, 15 };
	float vectorModule;
	Vector2 normalizeDirect;


	while (!WindowShouldClose())
	{
		Rectangle nave = { ship.position.x, ship.position.y , 50, 30 };
		mousePosition = GetMousePosition();

		//ship.position = {(float) GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

		Vector2 vectorDirection = { mousePosition.x - ship.position.x,  mousePosition.y - ship.position.y };



		float arcTan = atan2(vectorDirection.y, vectorDirection.x);
		float angle = arcTan * 180 / PI;

		ship.rotation = angle;

		vectorModule = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));

		normalizeDirect = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };

		//input
		input(ship, normalizeDirect);


		/*if (CheckCollisionPointCircle(mousePosition, Vector2{ ship.position.x + 26, ship.position.y + 26 }, ship.radius))
		{
			ship.position = { (float)GetRandomValue(90, 1000), (float)GetRandomValue(90, 700) };

		}*/

		BeginDrawing();
		ClearBackground(BLACK);


		//DrawCircleLines(ship.position.x + 26, ship.position.y + 26, ship.radius, WHITE);

		DrawText(TextFormat("Angle: %f", ship.rotation), 200, 80, 20, RED);
		DrawRectanglePro(nave, pivot, ship.rotation, RED);
		DrawLineEx(Vector2{ nave.x, nave.y }, mousePosition, 1, WHITE);
		DrawFPS(10, 10);

		//DrawTextureEx(shipSprite, ship.position, ship.rotation, 1, WHITE);


		DrawPixelV(mousePosition, RED);

		EndDrawing();
	}

	//UnloadTexture(shipSprite);

	CloseWindow();
}

