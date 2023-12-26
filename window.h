#include "menu.h"

void Window::Init() {
	InitWindow(size.x, size.y, title.c_str());
	SetTargetFPS(GetMonitorRefreshRate(0));
}

bool Window::ProcessPerFrame() {
	if (WindowShouldClose()) run = 0;

	if (IsKeyDown(KEY_ONE)) bulletType = 0;
	if (IsKeyDown(KEY_TWO)) bulletType = 1;
	if (IsKeyDown(KEY_THREE)) bulletType = 2;

	DrawTexture(background, 0, 0, WHITE);

	if (page == 1) {
		uend = std::chrono::high_resolution_clock::now();
		rogueEnd = std::chrono::high_resolution_clock::now();
		auto pend = std::chrono::high_resolution_clock::now();

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) shoot();

		if ((pend - pstart).count() / 10000000 > 3000) {
			asteroids.push_back(asteroidSpawn());
			stage++;
			pstart = std::chrono::high_resolution_clock::now();
			powerUPs.emplace_back(PowerUP(PowerUPIdCount++, dis(gen) % 6, (dis(gen) % 50 + 150) / 100));
		}

		if (stage > 1) {
			for (RogueEnemy rogueEnemy : rogueEnemies) {
				rogueEnemy.draw();
			}
		}

		ProcessPerTick();

		if (score > highscore) highscore = score;

		for (int i = 0; i < asteroids.size() - 1; i++) {
			if (asteroids.size()) {
				asteroids[i].draw();
			}
			else {
				break;
			}
		}
		for (Bullet& bul : bullets) {
			bul.draw();
		}
		for (PowerUP& powerup : powerUPs) {
			powerup.draw();
		}
		for (MiniBullet minibullet : miniBullets) {
			minibullet.draw();
		}
		for (Gear gear : gears) {
			gear.draw();
		}
		for (Explosion explosion : explosions) {
			explosion.draw();
		}
		player.draw();
		if (shield.active) {
			shield.draw();
		}
		DrawTexture(menuUI, 0, 230, WHITE);
		DrawTextEx(font, (std::to_string(score)).c_str(), Vector2f(50, window_size.y - 30 - 70 / 2), 70, 2, GOLD);
		DrawTextEx(font, (std::to_string(totalcoins)).c_str(), Vector2f(window_size.x - 175, window_size.y - 30 - 70 / 2), 70, 0, GOLD);

		rocketTexture.width = 50;
		rocketTexture.height = 125;
		for (int i = 0; i < min(rocketsAvailable, 8); i++) {
			DrawTextureEx(rocketTexture, Vector2f(window_size.x - 130, window_size.y - i*60 - 150), -90, 1, WHITE);
		}DrawTextEx(font, "Q", Vector2f(window_size.x - 160, window_size.y - 175) - Vector2f(MeasureTextEx(font, "Q", 64, 0).x/2, MeasureTextEx(font, "Q", 64, 0).y/2), 64, 0, Colorf(255,255,255,128));

		if (player.health > maxHealth) player.health = maxHealth;
		if (player.health <= 0) {
			player.health = 0;
			endGame();
		}
		DrawTexture(healthTextures[min(player.health,11)], 20, 20, WHITE);


		DrawTextEx(font, "1", Vector2f(0, 540), 32, 2, LIGHTGRAY);
		DrawTextEx(font, "2", Vector2f(0, 640), 32, 2, LIGHTGRAY);
		DrawTextEx(font, "3", Vector2f(0, 740), 32, 2, LIGHTGRAY);

		ImageButton Bullet1(Vector2f(0, 550), bulletTextures[0], Vector2f(100, 100), Vector2f(25, 50), 5, BLANK, BLANK, Colorf(255, 255, 255, (bulletType == 0) ? 255 : 100));
		ImageButton Bullet2(Vector2f(0, 650), bulletTextures[1], Vector2f(100, 100), Vector2f(25, 50), 5, BLANK, BLANK, Colorf(255, 255, 255, (bulletType == 1) ? 255 : 100));
		ImageButton Bullet3(Vector2f(0, 750), bulletTextures[2], Vector2f(100, 100), Vector2f(25, 50), 5, BLANK, BLANK, Colorf(255, 255, 255, (bulletType == 2) ? 255 : 100));

		Bullet1.draw();
		Bullet2.draw();
		Bullet3.draw();

	}
	else if (page == 0) {
		menu();
	}
	else if (page == 2) {
		shop();
	}
	else if (page == 3) {
		help();
	}

	DrawFPS(0, 0);

	BeginDrawing();
	EndDrawing();
	ClearBackground(SKYBLUE);

	return false;
}

bool Window::ProcessPerTick() {
	auto tickend = std::chrono::high_resolution_clock::now();
	if ((tickend - tick).count() / 10000000) {
		tick = std::chrono::high_resolution_clock::now();

		if ((rogueEnd - rogueStart).count() / 10000000 > 1500) {
			for (int i = 0; i < min(stage, 4)-1; i++) {
				rogueEnemies.push_back(RogueEnemy(RogueEnemyIdCount++, dis(gen)));
			}
			rogueStart = std::chrono::high_resolution_clock::now();
		}

		if (IsKeyDown(KEY_D)) player.move(Vector2f(1, 0));
		if (IsKeyDown(KEY_S)) player.move(Vector2f(0, 1));
		if (IsKeyDown(KEY_A)) player.move(Vector2f(-1, 0));
		if (IsKeyDown(KEY_W)) player.move(Vector2f(0, -1));

		for (int i = 0; i < asteroids.size() - 1; i++) {
			if (asteroids.size()) {
				asteroids[i].update();
			}
			else {
				break;
			}
		}
		for (Bullet& bul : bullets) {
			bul.update();
		}
		for (PowerUP& powerup : powerUPs) {
			powerup.update();
		}
		for (Gear& gear : gears) {
			gear.update();
		}
		for (MiniBullet& minibullet : miniBullets) {
			minibullet.update();
		}
		for (RogueEnemy& rogueEnemy : rogueEnemies) {
			rogueEnemy.update();
		}
		for (Explosion& explosion : explosions) {
			explosion.update();
		}
		shield.update();
	}

	return false;
}