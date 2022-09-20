#include <iostream>
#include "raylib.h"
#include "spaceShip.h"

using namespace std;

Ship ship;

int main()
{
	float screenWidht = 1024;
	float screenHeight = 768;

	InitWindow(screenWidht, screenHeight, "Asteroids");


	Texture2D shipSprite = LoadTexture("assets/bluespaceship.png");

	Vector2 mousePosition;

	Rectangle nave = { GetScreenWidth() / 2, GetScreenHeight() / 2 , 15, 8};
	Vector2 pivot = {nave.x + 7.5, nave.y + 4};

	initShip(ship);

	while (!WindowShouldClose())
	{
		mousePosition = GetMousePosition();

		//ship.position = {(float) GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

		//Vector2 vectorDirection = {ship.position - mousePosition};

		HideCursor();


		if (CheckCollisionPointCircle(mousePosition, Vector2{ ship.position.x + 26, ship.position.y + 26 }, ship.radius))
		{
			ship.position = { (float)GetRandomValue(90, 1000), (float)GetRandomValue(90, 700) };

		}

		BeginDrawing();
		ClearBackground(BLACK);


		DrawCircleLines(ship.position.x + 26, ship.position.y + 26, ship.radius, WHITE);
		DrawRectanglePro(nave, pivot, 0, RED);
		///*DrawTextureEx(shipSprite, ship.position, 0, 1, WHITE);
		//*/DrawTextureEx(shipSprite, ship.position, 90, 1, WHITE);
		DrawPixelV(mousePosition, WHITE);



		EndDrawing();
	}

	//UnloadTexture(shipSprite);

	CloseWindow();
}