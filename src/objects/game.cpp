#include "game.h"

#include <iostream>

#include "bullets.h"
#include "asteroid.h"
#include "spaceman.h"


extern Ship ship;

extern Asteroid bigAsteroids[maxBigAsteroids];
extern Asteroid mediumAsteroids[maxMediumAsteroids];
extern Asteroid smallAsteroids[maxSmallAsteroids];
extern Asteroid auxAsteroids[maxAuxAsteroids];
extern Asteroid asteroids[maxAsteroids];

extern Bullet bullets[maxBullets];

extern Spaceman spaceman;
extern Spaceman menuSpaceman;

static void reset(float& score, int& playOnce);

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
	Texture2D spacemanSprite = LoadTexture("res/spaceman.png");
	Texture2D spacemanSpriteFront = LoadTexture("res/spacemanFront.png");

	Font font = LoadFontEx("res/font.ttf", 40, 0, 0);
	Font titleFont = LoadFontEx("res/titleFont.ttf", 100, 0, 0);
	Font gameFont = LoadFontEx("res/futuristFont.ttf", 100, 0, 0);

	Sound laserShot = LoadSound("res/shot.wav");
	Sound explosion1 = LoadSound("res/explosion01.wav");
	Sound explosion2 = LoadSound("res/explosion02.wav");
	Sound explosion3 = LoadSound("res/explosion03.wav");
	Sound explosion4 = LoadSound("res/explosion04.wav");
	Sound explosion5 = LoadSound("res/explosion05.wav");
	Sound explosion6 = LoadSound("res/explosion06.wav");
	Sound explosion7 = LoadSound("res/explosion07.wav");
	Sound explosion8 = LoadSound("res/explosion08.wav");
	Sound explosion9 = LoadSound("res/explosion09.wav");
	Sound shipExplosion = LoadSound("res/shipExplosion.wav");
	Sound gameOver = LoadSound("res/gameOver.wav");


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
	SetSoundVolume(explosion1, 0.3f);
	SetSoundVolume(explosion2, 0.3f);
	SetSoundVolume(explosion3, 0.3f);
	SetSoundVolume(explosion4, 0.3f);
	SetSoundVolume(explosion5, 0.3f);
	SetSoundVolume(explosion6, 0.3f);
	SetSoundVolume(explosion7, 0.3f);
	SetSoundVolume(explosion8, 0.3f);
	SetSoundVolume(explosion9, 0.3f);
	SetSoundVolume(gameOver, 0.3f);

	initSpaceman(spaceman);
	initSpaceman(menuSpaceman);

	menuSpaceman.position = {65, 40 };
	menuSpaceman.speed.x = 100;

	for (int i = 0; i < maxBigAsteroids; i++)
	{
		initAsteroid(bigAsteroids[i], static_cast<float>(GetRandomValue(10, 500)), static_cast<float>(GetRandomValue(10, 500)), 0, AsteroidSize::Big);
	}
	for (int i = 0; i < maxMediumAsteroids; i++)
	{
		initAsteroid(mediumAsteroids[i], static_cast<float>(GetRandomValue(10, 500)), static_cast<float>(GetRandomValue(10, 500)), 0, AsteroidSize::Medium);
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		initAsteroid(smallAsteroids[i], static_cast<float>(GetRandomValue(10, 500)), static_cast<float>(GetRandomValue(10, 500)), 0, AsteroidSize::Small);
	}
	for (int i = 0; i < maxAuxAsteroids; i++)
	{
		auxAsteroids[i].isActive = false;

	}

	int countAsteroids = 0;


	for (int i = 0; i < maxBigAsteroids; i++)
	{
		asteroids[countAsteroids] = bigAsteroids[i];
		countAsteroids++;

	}
	for (int i = 0; i < maxMediumAsteroids; i++)
	{
		asteroids[countAsteroids] = mediumAsteroids[i];
		countAsteroids++;
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		asteroids[countAsteroids] = smallAsteroids[i];
		countAsteroids++;
	}
	for (int i = 0; i < maxAuxAsteroids; i++)
	{
		asteroids[countAsteroids] = auxAsteroids[i];
		countAsteroids++;

	}

	int currentBullets = 0;

	int currentScreen = Menu;
	float score = 0.0f;
	bool firstLife = true;
	int playOnce = 0;


	float frameWidth = static_cast<float>(spacemanSprite.width / 3);
	float frameHeight = static_cast<float>(spacemanSprite.height / 4);
	int maxFrames = static_cast<int>(spacemanSprite.width / frameWidth);

	float timer = 0.0f;
	int frame = 0;

	while (!WindowShouldClose() && !gameFinish)
	{

		mousePosition = GetMousePosition();

		Vector2 vectorDirection = { mousePosition.x - ship.position.x,  mousePosition.y - ship.position.y };

		float arcTan = atan2(vectorDirection.y, vectorDirection.x);
		float angle = arcTan * 180 / PI;

		vectorModule = static_cast<float>(sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2)));

		normalizeDirect = { vectorDirection.x / vectorModule, vectorDirection.y / vectorModule };


		if (!menuSpaceman.isGoingBack)
		{
			menuSpaceman.position.x += menuSpaceman.speed.x * GetFrameTime();
		}
		else if (menuSpaceman.isGoingBack)
		{
			menuSpaceman.position.x -= menuSpaceman.speed.x * GetFrameTime();
		}

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

			if (spaceman.isActive)
			{
				if (!spaceman.isGoingBack)
				{
					spaceman.position.x += spaceman.speed.x * GetFrameTime();
				}
				else if (spaceman.isGoingBack)
				{
					spaceman.position.x -= spaceman.speed.x * GetFrameTime();
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

		if (CheckCollisionCircleRec(ship.position, static_cast<float>(ship.radius), Rectangle{ spaceman.position.x,spaceman.position.y, spaceman.x, spaceman.y }) && ship.isAlive && spaceman.isActive)
		{
			PlaySoundMulti(shipExplosion);
			ship.lifes -= 2;
			ship.isAlive = false;
		}

		for (int i = 0; i < maxAsteroids; i++)
		{
			if (collisionCircleCircle(Vector2{ static_cast<float>(asteroids[i].x) , static_cast<float>(asteroids[i].y) }, static_cast<float>(asteroids[i].radius), Vector2{ static_cast<float>(ship.position.x) , static_cast<float>(ship.position.y) }, static_cast<float>(ship.radius)) && ship.isAlive && asteroids[i].isActive)
			{
				PlaySoundMulti(shipExplosion);
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
				if (CheckCollisionCircleRec(Vector2{ bullets[j].x , bullets[j].y }, bullets[j].radius, Rectangle{ spaceman.position.x,spaceman.position.y, spaceman.x, spaceman.y }) && bullets[j].isActive && spaceman.isActive)
				{
					spaceman.lifes--;
					bullets[j].isActive = false;
				}

				if (collisionCircleCircle(Vector2{ static_cast<float>(bullets[j].x) , static_cast<float>(bullets[j].y) }, bullets[j].radius, Vector2{ static_cast<float>(asteroids[i].x) , static_cast<float>(asteroids[i].y) }, static_cast<float>(asteroids[i].radius)) && asteroids[i].isActive && bullets[j].isActive)
				{
					int randomSound = GetRandomValue(1, 9);

					switch (randomSound)
					{
					case 1:
						PlaySoundMulti(explosion1);
						break;
					case 2:
						PlaySoundMulti(explosion2);
						break;
					case 3:
						PlaySoundMulti(explosion3);
						break;
					case 4:
						PlaySoundMulti(explosion4);
						break;
					case 5:
						PlaySoundMulti(explosion5);
						break;
					case 6:
						PlaySoundMulti(explosion6);
						break;
					case 7:
						PlaySoundMulti(explosion7);
						break;
					case 8:
						PlaySoundMulti(explosion8);
						break;
					case 9:
						PlaySoundMulti(explosion9);
						break;
					default:
						break;
					}


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

					separateAsteroids(i);

				}

			}

		}

		if (anyAsteroidAlive())
		{
			countAsteroids = 0;
			for (int i = 0; i < maxBigAsteroids; i++)
			{
				asteroids[countAsteroids] = bigAsteroids[i];
				countAsteroids++;
			}
			for (int i = 0; i < maxMediumAsteroids; i++)
			{
				asteroids[countAsteroids] = mediumAsteroids[i];
				countAsteroids++;
			}
			for (int i = 0; i < maxSmallAsteroids; i++)
			{
				asteroids[countAsteroids] = smallAsteroids[i];
				countAsteroids++;
			}
			for (int i = 0; i < maxAuxAsteroids; i++)
			{
				asteroids[countAsteroids] = auxAsteroids[i];
				countAsteroids++;

			}
		}

		if (spaceman.lifes <= 0)
			spaceman.isActive = false;


		float anyKeyTextLenght = MeasureTextEx(titleFont, "Press any key to start", static_cast<float>(titleFont.baseSize / 2), 0).x;
		Vector2 deadTextLenght = MeasureTextEx(gameFont, "Game Over", static_cast<float>(gameFont.baseSize), 0);

		timer += GetFrameTime();

		if (timer >= 0.15)
		{
			timer = 0;
			frame += 1;
		}

		if (!spaceman.isGoingBack)
		{
			frame = frame % maxFrames;
		}

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
			drawMenu(playButton, pauseButton, creditButton, quitButton, titleFont, spacemanSprite, frameWidth, frameHeight, frame);

			break;
		case Game:

			if (firstLife)
			{
				DrawTextEx(titleFont, "Press any key to start", Vector2{ static_cast<float>((GetScreenWidth() / 2) - (anyKeyTextLenght / 2)), static_cast<float>(GetScreenHeight() / 2) }, static_cast<float>(titleFont.baseSize / 2), 0, WHITE);
			}

			if (checkShipDead() && ship.position.x != 0)
			{
				if (playOnce == 0)
				{
					PlaySoundMulti(gameOver);
					playOnce++;
				}
				DrawTextEx(gameFont, "Game Over", Vector2{ static_cast<float>(GetScreenWidth() / 2 - deadTextLenght.x / 2), static_cast<float>(GetScreenHeight() / 2) - deadTextLenght.y / 2 }, static_cast<float>(gameFont.baseSize), 0, RED);

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Menu;
					reset(score, playOnce);
					pause = false;
					firstLife = true;

				}
			}

			drawGame(shipSprite, asteroidSprite, smallPauseButton, score, shipSpriteNitro, titleFont, spacemanSprite, frameWidth, frameHeight, frame, bullet);

			if (CheckCollisionPointRec(mousePosition, Rectangle{ -3, static_cast<float>(GetScreenHeight() - 45), static_cast<float>(pauseButton.width) , static_cast<float>(pauseButton.height) }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				pause = !pause;

			pauseMode(playButton, quitButton, mousePosition, pause, firstLife, currentScreen, playOnce, score);

			break;
		case Options:
			optionsBoxes(currentScreen, smallCreditButtons);
			drawOptions(smallCreditButtons, font, titleFont, leftClick, rightClick);
			break;
		case Options2:
			options2Boxes(currentScreen, smallCreditButtons);
			drawOptions2(smallCreditButtons, font, titleFont, gameFont, spacemanSpriteFront, asteroidSprite);
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
	UnloadTexture(spacemanSprite);
	UnloadTexture(spacemanSpriteFront);

	UnloadFont(font);
	UnloadFont(titleFont);

	StopSoundMulti();
	UnloadSound(laserShot);
	UnloadSound(explosion1);
	UnloadSound(explosion2);
	UnloadSound(explosion3);
	UnloadSound(explosion4);
	UnloadSound(explosion5);
	UnloadSound(explosion6);
	UnloadSound(explosion7);
	UnloadSound(explosion8);
	UnloadSound(explosion9);
	UnloadSound(shipExplosion);
	UnloadSound(gameOver);
	CloseAudioDevice();

	CloseWindow();
}

void input(Vector2 normalizeDirect)
{
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && ship.isAlive)
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

	if (spaceman.position.x > GetScreenWidth())
	{
		spaceman.position.y = spaceman.position.y + 50;
		spaceman.isGoingBack = true;
	}
	if (spaceman.position.x < 0)
	{
		spaceman.position.y = spaceman.position.y + 50;
		spaceman.isGoingBack = false;
	}
	if (spaceman.position.y > GetScreenHeight())
	{
		spaceman.position.y = 80;
	}

	if (menuSpaceman.position.x > 930)
	{
		menuSpaceman.isGoingBack = true;
	}
	if (menuSpaceman.position.x < 65)
	{
		
		menuSpaceman.isGoingBack = false;
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

void drawMenu(Texture2D playButton, Texture2D pauseButton, Texture2D creditButton, Texture2D quitButton, Font titleFont, Texture2D spacemanSprite, float frameWidth, float frameHeight, int frame)
{
	int titleLength = static_cast<int>(MeasureTextEx(titleFont, "Remasteroids", static_cast<float>(titleFont.baseSize), 0).x);

	DrawTexture(playButton, -3, 350, WHITE);
	DrawTexture(pauseButton, -3, 450, WHITE);
	DrawTexture(creditButton, -3, 550, WHITE);
	DrawTexture(quitButton, -3, 650, WHITE);

	DrawRectangleLines(static_cast<int>(GetScreenWidth() / 2 - titleLength / 2), 90, titleLength, 90, WHITE);

	DrawTextEx(titleFont, "Remasteroids", Vector2{ static_cast<float>(GetScreenWidth() / 2 - titleLength / 2), 100 }, static_cast<float>(titleFont.baseSize), 0, WHITE);

	

	if (!menuSpaceman.isGoingBack)
	{
		DrawTextureRec(spacemanSprite,
			Rectangle{ (frameWidth * frame) + 12, static_cast<float>(spacemanSprite.height / 3.25), frameWidth, frameHeight },
			menuSpaceman.position,
			WHITE);
	}
	else if (menuSpaceman.isGoingBack)
	{
		DrawTextureRec(spacemanSprite,
			Rectangle{ (frameWidth * frame) + 12 , static_cast<float>(spacemanSprite.height / 1.24), frameWidth, frameHeight },
			menuSpaceman.position,
			WHITE);
	}

}

void creditBoxes(int& currentScreen, Texture2D creditButtons, Texture2D smallCreditButtons)
{
	Rectangle creditBox = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 150,static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };
	Rectangle creditBox1 = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 250, static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };
	Rectangle creditBox2 = { -3, static_cast<float>(GetScreenHeight() - 70), static_cast<float>(smallCreditButtons.width), static_cast<float>(smallCreditButtons.height) };
	Rectangle creditBox3 = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 350, static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };
	Rectangle creditBox4 = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 450, static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };
	Rectangle creditBox5 = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 550, static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };
	Rectangle creditBox6 = { static_cast<float>(GetScreenWidth() / 2 - creditButtons.width / 2), 50, static_cast<float>(creditButtons.width), static_cast<float>(creditButtons.height) };

	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox6)))
		OpenURL("https://opengameart.org/node/78354");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox)))
		OpenURL("https://opengameart.org/content/a-layered-asteroid-rock");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox1)))
		OpenURL("https://opengameart.org/content/square-gaming-font-free");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox3)))
		OpenURL("https://opengameart.org/content/laser-fire");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox4)))
		OpenURL("https://opengameart.org/content/9-explosion-sounds");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox5)))
		OpenURL("https://tgodd.itch.io/");
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), creditBox2)))
		currentScreen = Menu;

}

void drawCredits(Font font, Texture2D creditButtons, Texture2D smallCreditButtons)
{
	float creditTextLenght = static_cast<float>(MeasureTextEx(font, "Asteroid by FunwithPixels", static_cast<float>(font.baseSize), 0).x);
	float creditTextLenght1 = static_cast<float>(MeasureTextEx(font, "Font by openikino", static_cast<float>(font.baseSize), 0).x);
	float creditTextLenght2 = static_cast<float>(MeasureTextEx(font, "Laser sound by Dklon", static_cast<float>(font.baseSize), 0).x);
	float creditTextLenght3 = static_cast<float>(MeasureTextEx(font, "Explosion sounds by Viktor.Hahn", static_cast<float>(font.baseSize / 1.22), 0).x);
	float creditTextLenght4 = static_cast<float>(MeasureTextEx(font, "Spaceman by DoubleU Creativity", static_cast<float>(font.baseSize / 1.22), 0).x);
	float creditTextLenght5 = static_cast<float>(MeasureTextEx(font, "Itch.io", static_cast<float>(font.baseSize), 0).x);

	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 50, WHITE);
	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 150, WHITE);
	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 250, WHITE);
	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 350, WHITE);
	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 450, WHITE);
	DrawTexture(creditButtons, GetScreenWidth() / 2 - creditButtons.width / 2, 550, WHITE);
	DrawTextureEx(smallCreditButtons, Vector2{ -3, static_cast<float>(GetScreenHeight() - 70) }, 0, 1, WHITE);


	DrawTextEx(font, TextFormat("Spaceman by DoubleU Creativity"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - creditTextLenght4 / 2), 70 }, static_cast<float>(font.baseSize / 1.22), 0, AQUA);
	DrawTextEx(font, TextFormat("Asteroid by FunwithPixels"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - creditTextLenght / 2)  , 170 }, static_cast<float>(font.baseSize), 0, AQUA);
	DrawTextEx(font, TextFormat("Font by openikino"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - creditTextLenght1 / 2)  , 270 }, static_cast<float>(font.baseSize), 0, AQUA);
	DrawTextEx(font, TextFormat("Laser Sound by Dklon"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - creditTextLenght2 / 2)  , 370 }, static_cast<float>(font.baseSize), 0, AQUA);
	DrawTextEx(font, TextFormat("Explosion sounds by Viktor.Hahn"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - creditTextLenght3 / 2)  , 470 }, static_cast<float>(font.baseSize / 1.22), 0, AQUA);
	DrawTextEx(font, TextFormat("Itch.io"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - creditTextLenght5 / 2), 570 }, static_cast<float>(font.baseSize), 0, AQUA);
	DrawTextEx(font, TextFormat("Back"), Vector2{ 130, static_cast<float>(GetScreenHeight() - 50) }, static_cast<float>(font.baseSize), 0, WHITE);
}

void optionsBoxes(int& currentScreen, Texture2D smallCreditButtons)
{
	Rectangle optionsBox = { -3, static_cast<float>(GetScreenHeight() - 70), static_cast<float>(smallCreditButtons.width), static_cast<float>(smallCreditButtons.height) };
	Rectangle optionsBox1 = { static_cast<float>(GetScreenWidth() - smallCreditButtons.width), static_cast<float>(GetScreenHeight() - 70), static_cast<float>(smallCreditButtons.width), static_cast<float>(smallCreditButtons.height) };

	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), optionsBox)))
		currentScreen = Menu;
	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), optionsBox1)))
		currentScreen = Options2;
}

void drawOptions(Texture2D smallCreditButtons, Font font, Font titleFont, Texture2D leftClick, Texture2D rightClick)
{
	DrawTextureEx(smallCreditButtons, Vector2{ static_cast<float>(GetScreenWidth() - smallCreditButtons.width), static_cast<float>(GetScreenHeight() - 70) }, 0, 1, WHITE);
	DrawTextureEx(smallCreditButtons, Vector2{ -3, static_cast<float>(GetScreenHeight() - 70) }, 0, 1, WHITE);
	DrawTexture(leftClick, 280, 500, WHITE);
	DrawTexture(rightClick, 580, 500, WHITE);


	DrawTextEx(font, TextFormat("Back"), Vector2{ 130, static_cast<float>(GetScreenHeight() - 50) }, static_cast<float>(font.baseSize), 0, WHITE);
	DrawTextEx(font, TextFormat("Next"), Vector2{ 920, static_cast<float>(GetScreenHeight() - 50) }, static_cast<float>(font.baseSize), 0, WHITE);
	DrawTextEx(titleFont, TextFormat("Remasteroids is a remastered\nversion of the classic game\n'Asteroids'. The objective of the\ngame is to shoot and destroy\nasteroids avoiding colliding with\nthe fragments that detach from\nthem."),
		Vector2{ 70, 50 },
		static_cast<float>(font.baseSize), 0, WHITE);
	DrawTextEx(titleFont, TextFormat("Shoot"), Vector2{ 287, 450 }, static_cast<float>(font.baseSize), 0, RED);
	DrawTextEx(titleFont, TextFormat("Accelerate"), Vector2{ 525, 450 }, static_cast<float>(font.baseSize), 0, RED);

}

void options2Boxes(int& currentScreen, Texture2D smallCreditButtons)
{
	Rectangle optionsBox = { -3, static_cast<float>(GetScreenHeight() - 70), static_cast<float>(smallCreditButtons.width), static_cast<float>(smallCreditButtons.height) };

	if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), optionsBox)))
		currentScreen = Options;

}

void drawOptions2(Texture2D smallCreditButtons, Font font, Font titleFont, Font gameFont, Texture2D spacemanSpriteFront, Texture2D asteroidSprite)
{
	float textLength = MeasureTextEx(gameFont, "Enemys", static_cast<float>(gameFont.baseSize), 0).x;


	DrawTextureEx(smallCreditButtons, Vector2{ -3, static_cast<float>(GetScreenHeight() - 70) }, 0, 1, WHITE);


	DrawTextEx(font, TextFormat("Back"), Vector2{ 130, static_cast<float>(GetScreenHeight() - 50) }, static_cast<float>(font.baseSize), 0, WHITE);
	DrawTextEx(gameFont, TextFormat("Enemys"),
		Vector2{ GetScreenWidth() / 2 - textLength / 2, 50 },
		static_cast<float>(gameFont.baseSize), 0, WHITE);

	
	DrawTextEx(gameFont, TextFormat("1 HP"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - 180), 170}, static_cast<float>(font.baseSize / 1.2), 0, RED);
	
	DrawTexturePro(asteroidSprite,
		Rectangle{ 0, 0, static_cast<float>(asteroidSprite.width) ,static_cast<float>(asteroidSprite.height) },
		Rectangle{ static_cast<float>(GetScreenWidth() / 2 - 150 ), static_cast<float>(250), 100, 100 },
		Vector2{ 100 / 2, 100 / 2 },
		0,
		WHITE);

	
	DrawTextEx(gameFont, TextFormat("1 HP"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - 20), 205 }, static_cast<float>(font.baseSize / 1.8), 0, RED);
	
	DrawTexturePro(asteroidSprite,
		Rectangle{ 0, 0, static_cast<float>(asteroidSprite.width) ,static_cast<float>(asteroidSprite.height) },
		Rectangle{ static_cast<float>(GetScreenWidth() / 2  ), static_cast<float>(250), 53, 53 },
		Vector2{ 53 / 2, 53 / 2 },
		0,
		WHITE);

	
	DrawTextEx(gameFont, TextFormat("1 HP"), Vector2{ static_cast<float>(GetScreenWidth() / 2 + 105), 220 }, static_cast<float>(font.baseSize / 2.4), 0, RED);
	
	DrawTexturePro(asteroidSprite,
		Rectangle{ 0, 0, static_cast<float>(asteroidSprite.width) ,static_cast<float>(asteroidSprite.height) },
		Rectangle{ static_cast<float>(GetScreenWidth() / 2 + 120), static_cast<float>(250), 30, 30 },
		Vector2{ 30 / 2, 30 / 2 },
		0,
		WHITE);


	DrawTextEx(gameFont, TextFormat("20 HP"), Vector2{ static_cast<float>(GetScreenWidth() / 2 - 53), 333 }, static_cast<float>(font.baseSize / 1.2), 0, RED);
	
	DrawTexturePro(spacemanSpriteFront,
		Rectangle{ 0, 0, static_cast<float>(spacemanSpriteFront.width) ,static_cast<float>(spacemanSpriteFront.height) },
		Rectangle{ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(420), 48 * 2, 64 * 2 },
		Vector2{ 48 * 2 / 2 , 64* 2 / 2 },
		0,
		WHITE);

	
	DrawTextEx(titleFont, TextFormat("When one of these kills you, you\nhave to press 'SPACE' to respawn.\n                Be careful..."), Vector2{ 50, 550 }, static_cast<float>(font.baseSize), 0, WHITE);

}

void drawGame(Texture2D shipSprite, Texture2D asteroidSprite, Texture2D smallPauseButton, float score, Texture2D shipSpriteNitro, Font titleFont, Texture2D spacemanSprite, float frameWidth, float frameHeight, int frame, Texture2D bullet)
{
	int scoreLength = static_cast<int>(MeasureTextEx(titleFont, "Score: %02.020f ", static_cast<float>(titleFont.baseSize / 2.5), 0).x);

	DrawTexture(smallPauseButton, -3, static_cast<int>(GetScreenHeight() - 45), WHITE);
	DrawRectangleLines(static_cast<int>(GetScreenWidth() / 2), 15, scoreLength, 40, WHITE);
	DrawTextEx(titleFont, TextFormat("Score: %02.02f ", score), Vector2{ 520, 20 }, static_cast<float>(titleFont.baseSize / 2.5), 0, WHITE);

	for (int i = 0; i < ship.lifes; i++)
	{
		DrawTexture(shipSprite, 180 + i * 50, 5, WHITE);
	}


	drawShip(shipSprite, shipSpriteNitro);
	for (int i = 0; i < maxAsteroids; i++)
	{
		drawAsteroid(asteroidSprite, i);

	}

	drawBullets(bullet);

	drawSpaceman(spacemanSprite, frameWidth, frameHeight, frame);

	DrawFPS(10, 10);

}

void reset(float& score, int& playOnce)
{
	ship.position = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) };
	ship.speed = { 0, 0 };
	ship.lifes = 3;
	ship.isAlive = false;
	score = 0;
	playOnce = 0;

	spaceman.isActive = true;
	spaceman.lifes = 20;
	spaceman.position = { 10, 80 };
	spaceman.isGoingBack = false;


	for (int i = 0; i < maxBullets; i++)
	{
		bullets[i].isActive = false;
	}

	for (int i = 0; i < maxAsteroids; i++)
	{
		asteroids[i].isActive = true;
	}


	int countAsteroids = 0;

	for (int i = 0; i < maxBigAsteroids; i++)
	{
		asteroids[countAsteroids] = bigAsteroids[i];
		countAsteroids++;
	}
	for (int i = 0; i < maxMediumAsteroids; i++)
	{
		asteroids[countAsteroids] = mediumAsteroids[i];
		countAsteroids++;
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		asteroids[countAsteroids] = smallAsteroids[i];
		countAsteroids++;
	}
	for (int i = 0; i < maxAuxAsteroids; i++)
	{
		asteroids[countAsteroids] = auxAsteroids[i];
		countAsteroids++;

	}

}

bool collisionCircleCircle(Vector2 center1, float radius1, Vector2 center2, float radius2)
{
	float distX = center1.x - center2.x;
	float distY = center1.y - center2.y;

	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= radius1 + radius2)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void pauseMode(Texture2D playButton, Texture2D quitButton, Vector2 mousePosition, bool& pause, bool& firstLife, int& currentScreen, int& playOnce, float& score)
{
	if (pause)
	{
		DrawTexture(playButton, GetScreenWidth() / 2 - quitButton.width / 2, 275, WHITE);
		DrawTexture(quitButton, GetScreenWidth() / 2 - quitButton.width / 2, 425, WHITE);

		if (CheckCollisionPointRec(mousePosition, Rectangle{ static_cast<float>(GetScreenWidth() / 2 - playButton.width / 2), 275, static_cast<float>(playButton.width) , static_cast<float>(quitButton.height) }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			pause = !pause;
		if (CheckCollisionPointRec(mousePosition, Rectangle{ static_cast<float>(GetScreenWidth() / 2 - quitButton.width / 2), 425, static_cast<float>(quitButton.width) ,static_cast<float>(quitButton.height) }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			currentScreen = Menu;
			reset(score, playOnce);
			pause = !pause;
			firstLife = true;
		}

	}
}

