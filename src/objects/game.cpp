#include <iostream>
#include "math.h"
#include "game.h"
#include "spaceShip.h"
#include "asteroid.h"


extern Ship ship;

extern Asteroid bigAsteroid[maxBigAsteroids];
extern Asteroid mediumAsteroid[maxMediumAsteroids];
extern Asteroid smallAsteroid[maxSmallAsteroids];
extern Asteroid asteroids[maxAsteroids];

void runGame()
{
	HideCursor();

	initShip(ship);

	Texture2D shipSprite = LoadTexture("res/bluespaceship.png");
	Texture2D cursor = LoadTexture("res/cursor.png");
	Texture2D asteroidSprite = LoadTexture("res/asteroid.png");
	Texture2D background = LoadTexture("res/background.png");
	Texture2D pauseButton = LoadTexture("res/buttonOption.png");
	Texture2D smallPauseButton = LoadTexture("res/buttonOption.png");
	Texture2D quitButton = LoadTexture("res/buttonQuit.png");
	Texture2D playButton = LoadTexture("res/buttonPlay.png");
	Texture2D creditButton = LoadTexture("res/buttonCredit.png");
	Texture2D creditButtons = LoadTexture("res/buttonCredits.png");
	Texture2D smallCreditButtons = LoadTexture("res/buttonCredits.png");

	Font font = LoadFontEx("res/font.ttf", 40, 0, 0);
	Font titleFont = LoadFontEx("res/titleFont.ttf", 100, 0, 0);


	Vector2 mousePosition;

	float vectorModule;
	Vector2 normalizeDirect;

	bool gameFinish = false;

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
	smallPauseButton.width = smallPauseButton.width / 3;
	smallPauseButton.height = smallPauseButton.height / 3;


	for (int i = 0; i < maxBigAsteroids; i++)
	{
		initAsteroid(bigAsteroid[i], GetRandomValue(10, 500), GetRandomValue(10, 500), 0, Big);
	}
	for (int i = 0; i < maxMediumAsteroids; i++)
	{
		initAsteroid(mediumAsteroid[i], GetRandomValue(10, 500), GetRandomValue(10, 500), 0, Medium);
	}

	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		initAsteroid(smallAsteroid[i], GetRandomValue(10, 500), GetRandomValue(10, 500), 0, Small);
	}

	int countAsteroids = 0;
	for (int i = 0; i < maxBigAsteroids; i++)
	{
		asteroids[countAsteroids] = bigAsteroid[i];
		countAsteroids++;
	}
	for (int i = 0; i < maxMediumAsteroids; i++)
	{
		asteroids[countAsteroids] = mediumAsteroid[i];
		countAsteroids++;

	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		asteroids[countAsteroids] = smallAsteroid[i];
		countAsteroids++;
	}

	int currentScreen = Menu;


	while (!WindowShouldClose() && !gameFinish)
	{
		mousePosition = GetMousePosition();

		Vector2 vectorDirection = { mousePosition.x - ship.position.x,  mousePosition.y - ship.position.y };

		float arcTan = atan2(vectorDirection.y, vectorDirection.x);
		float angle = arcTan * 180 / PI;

		vectorModule = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));

		normalizeDirect = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };


		teleportationBox(ship, shipSprite, asteroids, asteroidSprite);

		if (!pause && currentScreen == Game)
		{
			input(ship, normalizeDirect);
			ship.rotation = angle;

			for (int i = 0; i < maxAsteroids; i++)
			{
				asteroids[i].x += asteroids[i].speed.x * GetFrameTime();
				asteroids[i].y += asteroids[i].speed.y * GetFrameTime();
				asteroids[i].rotation++;
			}
		}

		for (int i = 0; i < maxAsteroids; i++)
		{
			if (CheckCollisionCircles(Vector2{ (float)asteroids[i].x , (float)asteroids[i].y }, asteroids[i].radius, Vector2{ ship.position.x , ship.position.y }, ship.radius))
			{
				ship.lifes--;
				ship.position.x = GetScreenWidth() / 2;
				ship.position.y = GetScreenHeight() / 2;
				ship.speed = { 0,0 };
			}

		}

		if (checkShipDead())
			ship.isAlive = false;



		BeginDrawing();

		DrawTexture(background, 0, 0, WHITE);

		switch (currentScreen)
		{
		case Menu:

			menuBoxes(currentScreen, playButton, pauseButton, creditButton, quitButton);
			drawMenu(playButton, pauseButton, creditButton, quitButton, titleFont);

			break;
		case Game:

			drawGame(ship, asteroids, shipSprite, asteroidSprite, smallPauseButton);

			if (CheckCollisionPointRec(mousePosition, Rectangle{ -3, (float)GetScreenHeight() - 45, (float)pauseButton.width , (float)pauseButton.height }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				pause = !pause;

			if (pause)
			{
				DrawTexture(playButton, GetScreenWidth() / 2 - quitButton.width / 2, 275, WHITE);
				DrawTexture(quitButton, GetScreenWidth() / 2 - quitButton.width / 2, 425, WHITE);

				if (CheckCollisionPointRec(mousePosition, Rectangle{ (float)GetScreenWidth() / 2 - playButton.width / 2, 275, (float)playButton.width , (float)quitButton.height }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					pause = !pause;
				if (CheckCollisionPointRec(mousePosition, Rectangle{ (float)GetScreenWidth() / 2 - quitButton.width / 2, 425, (float)quitButton.width , (float)quitButton.height }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					currentScreen = Menu;

			}

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

		drawCursor(cursor, mousePosition);
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

void teleportationBox(Ship& ship, Texture2D shipSprite, Asteroid asteroid[maxAsteroids], Texture2D asteroidSprite)
{
	if (ship.position.x > GetScreenWidth() + shipSprite.width - 5)
		ship.position.x = -4;
	if (ship.position.x < 0 - shipSprite.width + 5)
		ship.position.x = GetScreenWidth() + 4;

	if (ship.position.y > GetScreenHeight() + shipSprite.height - 5)
		ship.position.y = -4;
	if (ship.position.y < 0 - shipSprite.height + 5)
		ship.position.y = GetScreenHeight() + 4;

	for (int i = 0; i < maxAsteroids; i++)
	{
		if (asteroids[i].x > GetScreenWidth() + shipSprite.width / 2)
			asteroids[i].x = 0;
		if (asteroids[i].x < 0 - shipSprite.width / 2)
			asteroids[i].x = GetScreenWidth();

		if (asteroids[i].y > GetScreenHeight() + shipSprite.height / 2)
			asteroids[i].y = 0;
		if (asteroids[i].y < 0 - shipSprite.height / 2)
			asteroids[i].y = GetScreenHeight();
	}

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

void menuBoxes(int& currentScreen, Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton)
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

void drawMenu(Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton, Font titleFont)
{
	int titleLegth = MeasureText("Remasteroids", titleFont.baseSize) / 2;

	DrawTexture(playButton, -3, 350, WHITE);
	DrawTexture(pauseButton, -3, 450, WHITE);
	DrawTexture(creditButton, -3, 550, WHITE);
	DrawTexture(quitButton, -3, 650, WHITE);

	DrawRectangleLines((float)GetScreenWidth() / 2 - titleLegth - 110, 90, titleLegth + 550, 90, WHITE);

	DrawTextEx(titleFont, "Remasteroids", Vector2{ (float)GetScreenWidth() / 2 - titleLegth - 100, 100 }, titleFont.baseSize, 0, WHITE);

}

void creditBoxes(int& currentScreen, Texture2D creditButtons, Texture2D smallCreditButtons)
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
	DrawTextEx(font, TextFormat("Back"), Vector2{ 130, (float)GetScreenHeight() - 50 }, font.baseSize, 0, AQUA);
}

void drawGame(Ship ship, Asteroid asteroids[maxAsteroids], Texture2D shipSprite, Texture2D asteroidSprite, Texture2D smallPauseButton)
{
	//DrawCircleLines(ship.position.x, ship.position.y, ship.radius, WHITE);

	drawShip(shipSprite);
	for (int i = 0; i < maxAsteroids; i++)
	{
		//DrawCircleLines(asteroids[i].x, asteroids[i].y, asteroids[i].radius, WHITE);
		drawAsteroid(asteroidSprite, i);
	}

	DrawText(TextFormat("Lifes: %i", ship.lifes), GetScreenWidth() / 2 - 200, 10, 40, RED);
	DrawTexture(smallPauseButton, -3, (float)GetScreenHeight() - 45, WHITE);


	DrawFPS(10, 10);


}

