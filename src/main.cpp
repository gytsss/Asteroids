#include "raylib.h"
#include "objects/game.h"


int main()
{
	float screenWidht = 1024;
	float screenHeight = 768;

	InitWindow(screenWidht, screenHeight, "Asteroids");
	SetWindowState(FLAG_VSYNC_HINT);
	
	runGame();

	CloseWindow();
}

