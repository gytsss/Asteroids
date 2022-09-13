#include <iostream>
#include "raylib.h"

using namespace std;


int main()
{
	InitWindow(1366, 768, "Asteroids");


	Vector2 position{GetScreenWidth()/2 , GetScreenHeight()/2};


	while (!WindowShouldClose())
	{
		if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
		position = { GetMousePosition().x, GetMousePosition().y };


		BeginDrawing();

		ClearBackground(GREEN);
		
		DrawCircleV(position, 5, BLACK);


		EndDrawing();
	}

	CloseWindow();
}