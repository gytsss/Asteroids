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
	Texture2D background = LoadTexture("res/background.png");
	Texture2D pauseButton = LoadTexture("res/buttonOption.png");
	Texture2D quitButton = LoadTexture("res/buttonQuit.png");
	Texture2D playButton = LoadTexture("res/buttonPlay.png");
	Texture2D creditButton = LoadTexture("res/buttonCredit.png");
	Texture2D creditButtons = LoadTexture("res/buttonCredits.png");
	Texture2D smallCreditButtons = LoadTexture("res/buttonCredits.png");

	Font font = LoadFontEx("res/font.ttf", 40, 0, 0);


	Vector2 mousePosition;

	float vectorModule;
	Vector2 normalizeDirect;

	Color colorCircle = WHITE;
	bool gameFinish = false;

	Asteroid asteroid = initAsteroid(GetRandomValue(10, 500), GetRandomValue(10, 500), 25, 0);

	asteroid.speed = { (float)GetRandomValue(70, 200), (float)GetRandomValue(70, 200) };

	int randomSpeedX;
	int randomSpeedY;

	do
	{
		randomSpeedX = GetRandomValue(-200, 200);

	} while (randomSpeedX > -70 && randomSpeedX < 70);

	do
	{
		randomSpeedY = GetRandomValue(-200, 200);

	} while (randomSpeedY >= -70 && randomSpeedY <= 70);


	asteroid.speed.x = randomSpeedX;
	asteroid.speed.y = randomSpeedY;

	bool pause = false;

	pauseButton.width = pauseButton.width / 2;
	pauseButton.height = pauseButton.height / 2;
	quitButton.width = quitButton.width / 2;
	quitButton.height = quitButton.height / 2;
	playButton.width = playButton.width / 2;
	playButton.height = playButton.height / 2;
	creditButton.width = creditButton.width / 2;
	creditButton.height = creditButton.height / 2;
	creditButtons.height = creditButtons.height / 2;
	smallCreditButtons.width = smallCreditButtons.width / 2;
	smallCreditButtons.height = smallCreditButtons.height / 2;

	
	int currentScreen = Credits;

	

	while (!WindowShouldClose() && !gameFinish)
	{
		mousePosition = GetMousePosition();

		Vector2 vectorDirection = { mousePosition.x - ship.position.x,  mousePosition.y - ship.position.y };

		float arcTan = atan2(vectorDirection.y, vectorDirection.x);
		float angle = arcTan * 180 / PI;

		vectorModule = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));

		normalizeDirect = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };


		teleportationBox(ship, shipSprite, asteroid, asteroidSprite);

		if (!pause && currentScreen == Game)
		{
			input(ship, normalizeDirect);

			ship.rotation = angle;
			asteroid.x += asteroid.speed.x * GetFrameTime();
			asteroid.y += asteroid.speed.y * GetFrameTime();
		}

		if (CheckCollisionCircles(Vector2{ (float)asteroid.x , (float)asteroid.y }, asteroid.radius, Vector2{ ship.position.x , ship.position.y }, ship.radius))
		{
			colorCircle = RED;
			ship.lifes--;
			ship.position.x = GetScreenWidth() / 2;
			ship.position.y = GetScreenHeight() / 2;
			ship.speed = { 0,0 };
		}
		else
			colorCircle = WHITE;

		


		BeginDrawing();

		DrawTexture(background, 0, 0, WHITE);

		switch (currentScreen)
		{
		case Menu:

			menuBoxes(currentScreen, playButton, pauseButton, creditButton, quitButton);
			drawMenu(playButton, pauseButton, creditButton, quitButton);

			break;
		case Game:
			DrawCircleLines(ship.position.x, ship.position.y, ship.radius, colorCircle);

			drawShip(shipSprite);
			DrawCircleLines(asteroid.x, asteroid.y, asteroid.radius, WHITE);
			drawAsteroid(asteroid, asteroidSprite);

			DrawText(TextFormat("Lifes: %i", ship.lifes), GetScreenWidth() / 2 - 200, 10, 40, RED);
			DrawTexture(pauseButton, -3, (float)GetScreenHeight() - 45, WHITE);

			if (CheckCollisionPointRec(mousePosition, Rectangle{ -3, (float)GetScreenHeight() - 45, (float)pauseButton.width , (float)pauseButton.height }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				pause = !pause;
			break;
		case Options:
			break;
		case Credits:
			
			creditBoxes(currentScreen, creditButtons, smallCreditButtons);
			drawCredits(font, creditButtons, smallCreditButtons);
			
			break;
		case Quit:
			gameFinish = true;
			break;
		default:
			break;
		}


		if (pause)
		{
			DrawTexture(quitButton, GetScreenWidth() / 2 - quitButton.width / 2, 500, WHITE);

		}


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

void menuBoxes(int &currentScreen, Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton)
{
	Rectangle menuBox1 = { -3, 350 , playButton.width, playButton.height };
	Rectangle menuBox2 = { -3, 450 , pauseButton.width, pauseButton.height };
	Rectangle menuBox3 = { -3, 550 , creditButton.width, creditButton.height };
	Rectangle menuBox4 = { -3, 650 , quitButton.width, quitButton.height };


	if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menuBox1)))
		currentScreen = Game;
	if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menuBox2)))
		currentScreen = Options;
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menuBox3)))
		currentScreen = Credits;
	if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), menuBox4)))
		currentScreen = Quit;
}

void drawMenu(Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton)
{
	DrawTexture(playButton, -3, 350, WHITE);
	DrawTexture(pauseButton, -3, 450, WHITE);
	DrawTexture(creditButton, -3, 550, WHITE);
	DrawTexture(quitButton, -3, 650, WHITE);

}

void creditBoxes(int &currentScreen, Texture2D creditButtons, Texture2D smallCreditButtons)
{
	Rectangle creditBox = { GetScreenWidth() / 2 - creditButtons.width / 2, 150, creditButtons.width, creditButtons.height };
	Rectangle creditBox1 = { GetScreenWidth() / 2 - creditButtons.width / 2, 250, creditButtons.width, creditButtons.height };
	Rectangle creditBox2 = { -3, (float)GetScreenHeight() - 70, smallCreditButtons.width, smallCreditButtons.height };

	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox)))
		OpenURL("https://opengameart.org/content/a-layered-asteroid-rock");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox1)))
		OpenURL("https://tgodd.itch.io/");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox2)))
		currentScreen = Menu;

}

void drawCredits(Font font, Texture2D creditButtons, Texture2D smallCreditButtons)
{
	float creditTextLenght = MeasureText("Itch.io", font.baseSize) / 2;

	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 150, WHITE);
	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 250, WHITE);
	DrawTextureEx(smallCreditButtons, Vector2{ -3, (float)GetScreenHeight() - 70 }, 0, 1, WHITE);


	DrawTextEx(font, TextFormat("Asteroid by FunwithPixels"), Vector2{ (float)GetScreenWidth() / 2 - 200  , 170 }, font.baseSize, 0, AQUA);
	DrawTextEx(font, TextFormat("Itch.io"), Vector2{ (float)GetScreenWidth() / 2 - creditTextLenght , 270 }, font.baseSize, 0, AQUA);
}

