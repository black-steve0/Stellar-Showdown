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

		if ((pend - pstart).count() / 10000000 > 100) {
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

		if (player.health > maxHealth) player.health = maxHealth;
		if (player.health <= 0) {
			player.health = 0;
			endGame();
		}
		DrawTexture(healthTextures[player.health], 20, 20, WHITE);
	}
	else if (page == 0) {
		menu();
	}
	else if (page == 2) {
		shop();
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