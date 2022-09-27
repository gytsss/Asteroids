#include "raylib.h"
#include "objects/game.h"


int main()
{
	float screenWidth = 1024;
	float screenHeight = 768;

	InitWindow(screenWidth, screenHeight, "Asteroids");
	SetWindowState(FLAG_VSYNC_HINT);
	
	runGame();

	CloseWindow();
}

