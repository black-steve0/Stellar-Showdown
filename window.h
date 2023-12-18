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
		auto end = std::chrono::high_resolution_clock::now();
		auto pend = std::chrono::high_resolution_clock::now();

		if ((end - start).count() / 10000000 > 10) {
			start = std::chrono::high_resolution_clock::now();
			if (IsKeyDown(KEY_SPACE)) shoot();
		}
		if ((pend - pstart).count() / 10000000 > 6000) {
			pstart = std::chrono::high_resolution_clock::now();
			powerUPs.emplace_back(PowerUP(PowerUPIdCount++, rand() % 4, (rand() % 50 + 150) / 100));
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
		for (Gear gear : gears) {
			gear.draw();
		}
		player.draw();
		DrawTexture(menuUI, 0, 230, WHITE);
		DrawText((std::to_string(score)).c_str(), 50, window_size.y - 30 - 50 / 2, 50, GOLD);

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

		if (IsKeyDown(KEY_D)) player.move(Vector2(1, 0));
		if (IsKeyDown(KEY_S)) player.move(Vector2(0, 1));
		if (IsKeyDown(KEY_A)) player.move(Vector2(-1, 0));
		if (IsKeyDown(KEY_W)) player.move(Vector2(0, -1));

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

		gears.push_back(Gear(GearIdCount++));

		for (Gear& gear : gears) {
			gear.update();
			std::cout << gear.position << std::endl;
		}
	}

	return false;
}