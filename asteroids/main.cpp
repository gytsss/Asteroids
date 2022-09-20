#include <iostream>
#include "raylib.h"
#include "spaceShip.h"
#include <cmath>


using namespace std;

Ship ship;

int main()
{
	float screenWidht = 1024;
	float screenHeight = 768;

	InitWindow(screenWidht, screenHeight, "Asteroids");
	HideCursor();


	Texture2D shipSprite = LoadTexture("assets/bluespaceship.png");

	Vector2 mousePosition;

	Rectangle nave = { GetScreenWidth() / 2, GetScreenHeight() / 2 , 50, 30 };
	Vector2 pivot = { 25, 15 };

	initShip(ship);

	while (!WindowShouldClose())
	{
		mousePosition = GetMousePosition();

		//ship.position = {(float) GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

		Vector2 vectorDirection = { mousePosition.x - ship.position.x,  mousePosition.y - ship.position.y };


		float arcTan = atan2 (vectorDirection.y, vectorDirection.x);
		float angle = arcTan * 180 / PI;


		ship.rotation = angle;


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

		DrawTextureEx(shipSprite, ship.position, ship.rotation, 1, WHITE);


		DrawPixelV(mousePosition, RED);

		EndDrawing();
	}

	//UnloadTexture(shipSprite);

	CloseWindow();
}