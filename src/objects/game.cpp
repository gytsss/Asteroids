#include <iostream>
#include "math.h"
#include "game.h"
#include "spaceShip.h"
#include "asteroid.h"
#include "bullets.h"


extern Ship ship;

extern Asteroid bigAsteroid[maxBigAsteroids];
extern Asteroid mediumAsteroid[maxMediumAsteroids];
extern Asteroid smallAsteroid[maxSmallAsteroids];
extern Asteroid auxAsteroid[maxAuxAsteroids];
extern Asteroid asteroids[maxAsteroids];

extern Bullet bullets[maxBullets];

void reset(float& score);

void runGame()
{
	int screenWidth = 1024;
	int screenHeight = 768;

	InitWindow(screenWidth, screenHeight, "Asteroids");
	SetWindowState(FLAG_VSYNC_HINT);
	InitAudioDevice();

	HideCursor();


	Texture2D shipSprite = LoadTexture("res/bluespaceship.png");
	Texture2D shipSpriteNitro = LoadTexture("res/bluespaceshipNitro.png");
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
	Texture2D leftClick = LoadTexture("res/leftclick.png");
	Texture2D rightClick = LoadTexture("res/rightclick.png");
	Texture2D bullet = LoadTexture("res/laserBullet.png");

	Font font = LoadFontEx("res/font.ttf", 40, 0, 0);
	Font titleFont = LoadFontEx("res/titleFont.ttf", 100, 0, 0);
	Font gameFont = LoadFontEx("res/futuristFont.ttf", 100, 0, 0);

	Sound laserShot = LoadSound("res/shot.wav");


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
	leftClick.width = leftClick.width / 3;
	leftClick.height = leftClick.height / 3;
	rightClick.width = rightClick.width / 3;
	rightClick.height = rightClick.height / 3;

	SetSoundVolume(laserShot, 0.15f);

	for (int i = 0; i < maxBigAsteroids; i++)
	{
		initAsteroid(bigAsteroid[i], static_cast<float>(GetRandomValue(10, 500)), static_cast<float>(GetRandomValue(10, 500)), 0, AsteroidSize::Big);
	}
	for (int i = 0; i < maxMediumAsteroids; i++)
	{
		initAsteroid(mediumAsteroid[i], static_cast<float>(GetRandomValue(10, 500)), static_cast<float>(GetRandomValue(10, 500)), 0, AsteroidSize::Medium);
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		initAsteroid(smallAsteroid[i], static_cast<float>(GetRandomValue(10, 500)), static_cast<float>(GetRandomValue(10, 500)), 0, AsteroidSize::Small);
	}
	for (int i = 0; i < maxAuxAsteroids; i++)
	{
		auxAsteroid[i].isActive = false;

	}

	int countAsteroids = 0;
	int currentAsteroids = 0;

	for (int i = 0; i < maxBigAsteroids; i++)
	{
		asteroids[countAsteroids] = bigAsteroid[i];
		countAsteroids++;
		currentAsteroids++;
	}
	for (int i = 0; i < maxMediumAsteroids; i++)
	{
		asteroids[countAsteroids] = mediumAsteroid[i];
		countAsteroids++;
		currentAsteroids++;
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		asteroids[countAsteroids] = smallAsteroid[i];
		countAsteroids++;
		currentAsteroids++;
	}
	for (int i = 0; i < maxAuxAsteroids; i++)
	{
		asteroids[countAsteroids] = auxAsteroid[i];
		countAsteroids++;

	}

	int currentBullets = 0;

	int currentScreen = Menu;
	float score = 0.0f;
	float firstLife = true;

	while (!WindowShouldClose() && !gameFinish)
	{

		mousePosition = GetMousePosition();

		Vector2 vectorDirection = { mousePosition.x - ship.position.x,  mousePosition.y - ship.position.y };

		float arcTan = atan2(vectorDirection.y, vectorDirection.x);
		float angle = arcTan * 180 / PI;

		vectorModule = static_cast<float>(sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2)));

		normalizeDirect = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };


		teleportationBox(shipSprite, asteroidSprite);

		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].x > GetScreenWidth() || bullets[i].x < 0 || bullets[i].y < 0 || bullets[i].y > GetScreenHeight())
				bullets[i].isActive = false;
		}


		if (!pause && currentScreen == Game)
		{
			input(normalizeDirect);
			ship.rotation = angle;

			for (int i = 0; i < maxAsteroids; i++)
			{
				asteroids[i].x += asteroids[i].speed.x * GetFrameTime();
				asteroids[i].y += asteroids[i].speed.y * GetFrameTime();
				asteroids[i].rotation++;
			}

			for (int i = 0; i < maxBullets; i++)
			{
				if (bullets[i].isActive)
				{
					bullets[i].x += bullets[i].speed.x * GetFrameTime() * 300;
					bullets[i].y += bullets[i].speed.y * GetFrameTime() * 300;
				}
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ship.isAlive)
			{
				PlaySoundMulti(laserShot);

				if (currentBullets >= maxBullets)
					currentBullets = 0;

				bullets[currentBullets] = initBullet(bullets[currentBullets], ship, vectorDirection);
				currentBullets++;

			}
		}

		for (int i = 0; i < maxAsteroids; i++)
		{
			if (CheckCollisionCircles(Vector2{ static_cast<float>(asteroids[i].x) , static_cast<float>(asteroids[i].y) }, static_cast<float>(asteroids[i].radius), Vector2{ static_cast<float>(ship.position.x) , static_cast<float>(ship.position.y) }, static_cast<float>(ship.radius)) && ship.isAlive && asteroids[i].isActive)
			{
				ship.lifes--;
				ship.isAlive = false;
			}

		}
		if (IsKeyReleased(KEY_SPACE) && !ship.isAlive)
		{
			ship.isAlive = true;
			ship.position.x = static_cast<float>(GetScreenWidth() / 2);
			ship.position.y = static_cast<float>(GetScreenHeight() / 2);
			ship.speed = { 0,0 };

		}

		for (int i = 0; i < maxAsteroids; i++)
		{
			for (int j = 0; j < maxBullets; j++)
			{
				if (CheckCollisionCircles(Vector2{ static_cast<float>(bullets[j].x) , static_cast<float>(bullets[j].y) }, bullets[j].radius, Vector2{ static_cast<float>(asteroids[i].x) , static_cast<float>(asteroids[i].y) }, static_cast<float>(asteroids[i].radius)) && asteroids[i].isActive && bullets[j].isActive)
				{
					switch (asteroids[i].size)
					{
					case AsteroidSize::Big:
						score += 10;
						break;
					case AsteroidSize::Medium:
						score += 5;
						break;
					case AsteroidSize::Small:
						score += 2.5;
						break;
					default:
						break;
					}

					asteroids[i].isActive = false;
					bullets[j].isActive = false;
					currentAsteroids--;

					separateAsteroids(currentAsteroids, i);

				}

			}

			if (currentAsteroids == 0)
			{
				countAsteroids = 0;
				for (int j = 0; j < maxBigAsteroids; j++)
				{
					asteroids[countAsteroids] = bigAsteroid[j];
					countAsteroids++;
					currentAsteroids++;
				}
				for (int j = 0; j < maxMediumAsteroids; j++)
				{
					asteroids[countAsteroids] = mediumAsteroid[j];
					countAsteroids++;
					currentAsteroids++;
				}
				for (int j = 0; j < maxSmallAsteroids; j++)
				{
					asteroids[countAsteroids] = smallAsteroid[j];
					countAsteroids++;
					currentAsteroids++;
				}
				for (int j = 0; j < maxAuxAsteroids; j++)
				{
					asteroids[countAsteroids] = auxAsteroid[j];
					countAsteroids++;

				}
			}

		}

		float anyKeyTextLenght = MeasureTextEx(titleFont, "Press any key to start", static_cast<float>(titleFont.baseSize / 2), 0).x;
		Vector2 deadTextLenght = MeasureTextEx(gameFont, "Game Over", static_cast<float>(gameFont.baseSize), 0);

		int anyKey = GetCharPressed();
		if (anyKey > 0 && firstLife)
		{
			initShip();
			firstLife = false;
		}

		if (checkShipDead())
		{
			ship.isAlive = false;

		}


		BeginDrawing();

		ClearBackground(BLACK);
		DrawTexture(background, 0, 0, WHITE);

		switch (currentScreen)
		{
		case Menu:

			menuBoxes(currentScreen, playButton, pauseButton, creditButton, quitButton);
			drawMenu(playButton, pauseButton, creditButton, quitButton, titleFont);

			break;
		case Game:
			if (firstLife)
			{
				DrawTextEx(titleFont, "Press any key to start", Vector2{ static_cast<float>((GetScreenWidth() / 2) - (anyKeyTextLenght / 2)), static_cast<float>(GetScreenHeight() / 2) }, static_cast<float>(titleFont.baseSize / 2), 0, WHITE);
			}

			if (checkShipDead() && ship.position.x != 0)
			{
				DrawTextEx(gameFont, "Game Over", Vector2{ static_cast<float>(GetScreenWidth() / 2 - deadTextLenght.x / 2), static_cast<float>(GetScreenHeight() / 2) - deadTextLenght.y / 2 }, static_cast<float>(gameFont.baseSize), 0, RED);
			}

			drawGame(shipSprite, asteroidSprite, smallPauseButton, score, shipSpriteNitro, titleFont);

			for (int i = 0; i < maxBullets; i++)
			{
				if (bullets[i].isActive)
				{

					DrawTexturePro(bullet,
						Rectangle{ 0, 0, static_cast<float>(bullet.width) ,static_cast<float>(bullet.height) },
						Rectangle{ static_cast<float>(bullets[i].x) , static_cast<float>(bullets[i].y), 70, 70 },
						Vector2{ 70 / 2, 70 / 2 },
						bullets[i].rotation,
						WHITE);
				}
			}

			if (CheckCollisionPointRec(mousePosition, Rectangle{ -3, static_cast<float>(GetScreenHeight() - 45), static_cast<float>(pauseButton.width) , static_cast<float>(pauseButton.height) }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				pause = !pause;

			if (pause)
			{
				DrawTexture(playButton, GetScreenWidth() / 2 - quitButton.width / 2, 275, WHITE);
				DrawTexture(quitButton, GetScreenWidth() / 2 - quitButton.width / 2, 425, WHITE);

				if (CheckCollisionPointRec(mousePosition, Rectangle{ static_cast<float>(GetScreenWidth() / 2 - playButton.width / 2), 275, static_cast<float>(playButton.width) , static_cast<float>(quitButton.height) }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					pause = !pause;
				if (CheckCollisionPointRec(mousePosition, Rectangle{ static_cast<float>(GetScreenWidth() / 2 - quitButton.width / 2), 425, static_cast<float>(quitButton.width) ,static_cast<float>(quitButton.height) }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					currentScreen = Menu;
					reset(score);
					pause = !pause;
					firstLife = true;
				}

			}

			break;
		case Options:
			optionsBoxes(currentScreen, smallCreditButtons);
			drawOptions(smallCreditButtons, font, titleFont, leftClick, rightClick);
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
	UnloadTexture(shipSpriteNitro);
	UnloadTexture(asteroidSprite);
	UnloadTexture(background);
	UnloadTexture(pauseButton);
	UnloadTexture(smallPauseButton);
	UnloadTexture(quitButton);
	UnloadTexture(playButton);
	UnloadTexture(creditButton);
	UnloadTexture(creditButtons);
	UnloadTexture(smallCreditButtons);
	UnloadTexture(leftClick);
	UnloadTexture(rightClick);
	UnloadTexture(cursor);
	UnloadTexture(bullet);

	UnloadFont(font);
	UnloadFont(titleFont);

	StopSoundMulti();
	UnloadSound(laserShot);

	CloseAudioDevice();

	CloseWindow();
}

void input(Vector2 normalizeDirect)
{
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		ship.speed.x += normalizeDirect.x;
		ship.speed.y += normalizeDirect.y;


	}

	ship.position.x += ship.speed.x * GetFrameTime() * 5;
	ship.position.y += ship.speed.y * GetFrameTime() * 5;

}

void teleportationBox(Texture2D shipSprite, Texture2D asteroidSprite)
{
	if (ship.position.x > GetScreenWidth() + shipSprite.width - 5)
		ship.position.x = -4;
	if (ship.position.x < 0 - shipSprite.width + 5)
		ship.position.x = static_cast<float>(GetScreenWidth() + 4);

	if (ship.position.y > GetScreenHeight() + shipSprite.height - 5)
		ship.position.y = -4;
	if (ship.position.y < 0 - shipSprite.height + 5)
		ship.position.y = static_cast<float>(GetScreenHeight() + 4);

	for (int i = 0; i < maxAsteroids; i++)
	{
		if (asteroids[i].x > GetScreenWidth() + asteroidSprite.width / 2)
			asteroids[i].x = 0;
		if (asteroids[i].x < 0 - asteroidSprite.width / 2)
			asteroids[i].x = static_cast<float>(GetScreenWidth());

		if (asteroids[i].y > GetScreenHeight() + asteroidSprite.height / 2)
			asteroids[i].y = 0;
		if (asteroids[i].y < 0 - asteroidSprite.height / 2)
			asteroids[i].y = static_cast<float>(GetScreenHeight());
	}

}

void drawCursor(Texture2D cursor, Vector2 mousePosition)
{
	DrawTexturePro(cursor,
		Rectangle{ 0, 0,static_cast<float>(cursor.width),static_cast<float>(cursor.height) },
		Rectangle{ mousePosition.x, mousePosition.y, 30, 30 },
		Vector2{ static_cast<float>(cursor.width / 2 + 5),static_cast<float>(cursor.height / 2 + 5) },
		0,
		WHITE);
}

void menuBoxes(int& currentScreen, Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton)
{
	Rectangle menuBox1 = { -3, 350 ,static_cast<float>(playButton.width), static_cast<float>(playButton.height) };
	Rectangle menuBox2 = { -3, 450 , static_cast<float>(pauseButton.width), static_cast<float>(pauseButton.height) };
	Rectangle menuBox3 = { -3, 550 , static_cast<float>(creditButton.width), static_cast<float>(creditButton.height) };
	Rectangle menuBox4 = { -3, 650 ,static_cast<float>(quitButton.width),static_cast<float>(quitButton.height) };


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
	int titleLength = static_cast<int>(MeasureTextEx(titleFont, "Remasteroids", static_cast<float>(titleFont.baseSize), 0).x);

	DrawTexture(playButton, -3, 350, WHITE);
	DrawTexture(pauseButton, -3, 450, WHITE);
	DrawTexture(creditButton, -3, 550, WHITE);
	DrawTexture(quitButton, -3, 650, WHITE);

	DrawRectangleLines(static_cast<int>(GetScreenWidth() / 2 - titleLength / 2), 90, titleLength, 90, WHITE);

	DrawTextEx(titleFont, "Remasteroids", Vector2{ static_cast<float>(GetScreenWidth() / 2 - titleLength / 2), 100 }, static_cast<float>(titleFont.baseSize), 0, WHITE);

}

void creditBoxes(int& currentScreen, Texture2D creditButtons, Texture2D smallCreditButtons)
{
	Rectangle creditBox = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 150,static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };
	Rectangle creditBox1 = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 250, static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };
	Rectangle creditBox2 = { -3, static_cast<float>(GetScreenHeight() - 70), static_cast<float>(smallCreditButtons.width), static_cast<float>(smallCreditButtons.height) };
	Rectangle creditBox3 = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 350, static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };
	Rectangle creditBox4 = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 450, static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };

	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox)))
		OpenURL("https://opengameart.org/content/a-layered-asteroid-rock");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox1)))
		OpenURL("https://opengameart.org/content/square-gaming-font-free");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox4)))
		OpenURL("https://tgodd.itch.io/");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox3)))
		OpenURL("https://opengameart.org/content/laser-fire");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox2)))
		currentScreen = Menu;

}

void drawCredits(Font font, Texture2D creditButtons, Texture2D smallCreditButtons)
{
	float creditTextLenght = static_cast<float>(MeasureText("Itch.io", font.baseSize) / 2);

	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 150, WHITE);
	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 250, WHITE);
	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 350, WHITE);
	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 450, WHITE);
	DrawTextureEx(smallCreditButtons, Vector2{ -3, static_cast<float>(GetScreenHeight() - 70) }, 0, 1, WHITE);


	DrawTextEx(font, TextFormat("Asteroid by FunwithPixels"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - 200)  , 170 }, static_cast<float>(font.baseSize), 0, AQUA);
	DrawTextEx(font, TextFormat("Font by openikino"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - 135)  , 270 }, static_cast<float>(font.baseSize), 0, AQUA);
	DrawTextEx(font, TextFormat("Laser Sound by Dklon"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - 170)  , 370 }, static_cast<float>(font.baseSize), 0, AQUA);
	DrawTextEx(font, TextFormat("Itch.io"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - creditTextLenght), 470 }, static_cast<float>(font.baseSize), 0, AQUA);
	DrawTextEx(font, TextFormat("Back"), Vector2{ 130, static_cast<float>(GetScreenHeight() - 50) }, static_cast<float>(font.baseSize), 0, WHITE);
}

void optionsBoxes(int& currentScreen, Texture2D smallCreditButtons)
{
	Rectangle optionsBox = { -3, static_cast<float>(GetScreenHeight() - 70), static_cast<float>(smallCreditButtons.width), static_cast<float>(smallCreditButtons.height) };

	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), optionsBox)))
		currentScreen = Menu;
}

void drawOptions(Texture2D smallCreditButtons, Font font, Font titleFont, Texture2D leftClick, Texture2D rightClick)
{
	DrawTextureEx(smallCreditButtons, Vector2{ -3, static_cast<float>(GetScreenHeight() - 70) }, 0, 1, WHITE);
	DrawTexture(leftClick, 280, 500, WHITE);
	DrawTexture(rightClick, 580, 500, WHITE);


	DrawTextEx(font, TextFormat("Back"), Vector2{ 130, static_cast<float>(GetScreenHeight() - 50) }, static_cast<float>(font.baseSize), 0, WHITE);
	DrawTextEx(titleFont, TextFormat("Remasteroids is a remastered\nversion of the classic game\n'Asteroids'. The objective of the\ngame is to shoot and destroy\nasteroids avoiding colliding with\nthe fragments that detach from\nthem."),
		Vector2{ 70, 50 },
		static_cast<float>(font.baseSize), 0, WHITE);
	DrawTextEx(titleFont, TextFormat("Shoot"), Vector2{ 287, 450 }, static_cast<float>(font.baseSize), 0, RED);
	DrawTextEx(titleFont, TextFormat("Accelerate"), Vector2{ 525, 450 }, static_cast<float>(font.baseSize), 0, RED);

}

void drawGame(Texture2D shipSprite, Texture2D asteroidSprite, Texture2D smallPauseButton, float score, Texture2D shipSpriteNitro, Font titleFont)
{
	int scoreLength = static_cast<int>(MeasureTextEx(titleFont, "Score: %02.020f ", static_cast<float>(titleFont.baseSize / 2.5), 0).x);

	DrawTexture(smallPauseButton, -3, static_cast<int>(GetScreenHeight() - 45), WHITE);
	DrawRectangleLines(static_cast<int>(GetScreenWidth() / 2), 15, scoreLength, 40, WHITE);
	DrawTextEx(titleFont, TextFormat("Score: %02.02f ", score), Vector2{ 520, 20 }, static_cast<float>(titleFont.baseSize / 2.5), 0, WHITE);

	for (int i = 0; i < ship.lifes; i++)
	{
		DrawTexture(shipSprite, 180 + i * 50, 5, WHITE);
	}

	if (ship.isAlive)
		DrawCircleLines(static_cast<int>(ship.position.x), static_cast<int>(ship.position.y), static_cast<float>(ship.radius), WHITE);

	drawShip(shipSprite, shipSpriteNitro);
	for (int i = 0; i < maxAsteroids; i++)
	{
		if (asteroids[i].isActive)
		{
			DrawCircleLines(static_cast<int>(asteroids[i].x), static_cast<int>(asteroids[i].y), static_cast<float>(asteroids[i].radius), WHITE);
		}
		drawAsteroid(asteroidSprite, i);

	}


	DrawFPS(10, 10);

}

void reset(float& score)
{
	ship.position = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
	ship.speed = { 0, 0 };
	ship.lifes = 3;
	ship.isAlive = false;
	score = 0;

	for (int i = 0; i < maxBullets - 1; i++)
	{
		bullets[i].isActive = false;
	}

	for (int i = 0; i < maxAsteroids - 1; i++)
	{
		asteroids[i].isActive = true;
	}

	for (int i = maxAsteroids - 1; i > maxAsteroids - maxAuxAsteroids; i--)
	{
		asteroids[i].isActive = false;
	}
}

