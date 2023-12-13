#include "menu.h"

void Window::Init() {
	ray::InitWindow(size.x, size.y, title.c_str());
	ray::SetTargetFPS(ray::GetMonitorRefreshRate(0));
}

bool Window::ProcessPerFrame() {
	if (ray::WindowShouldClose()) run = 0;

	if (ray::IsKeyDown(ray::KEY_ONE)) bulletType = 0;
	if (ray::IsKeyDown(ray::KEY_TWO)) bulletType = 1;
	if (ray::IsKeyDown(ray::KEY_THREE)) bulletType = 2;

	ray::DrawTexture(background, 0, 0, WHITE);

	if (page == 1) {
		auto end = std::chrono::high_resolution_clock::now();
		auto pend = std::chrono::high_resolution_clock::now();

		if ((end - start).count() / 10000000 > 10) {
			start = std::chrono::high_resolution_clock::now();
			if (ray::IsKeyDown(ray::KEY_SPACE)) bullets.emplace_back(Bullet(BulletIdCount++, ray::Vector2(player.position.x + player.size.x / 2 - bulletsize / 2 - 3, player.position.y - bulletsize / 2), bulletType, damage));
		}
		if ((pend - pstart).count() / 10000000 > 6000) {
			pstart = std::chrono::high_resolution_clock::now();
			powerUPs.emplace_back(PowerUP(PowerUPIdCount++, rand() % 4, (rand() % 50 + 150) / 100));
		}

		ProcessPerTick();

		if (score > highscore) highscore = score;

		player.draw();
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

		ray::DrawTexture(menuUI, 0, 230, WHITE);
		ray::DrawText((std::to_string(score)).c_str(), 50, window_size.y - 30 - 50 / 2, 50, GOLD);
	}
	else if (page == 0) {
		menu();
	}
	else if (page == 2) {
		shop();
	}

	ray::DrawFPS(0, 0);

	ray::BeginDrawing();
	ray::EndDrawing();
	ray::ClearBackground(SKYBLUE);

	return false;
}

bool Window::ProcessPerTick() {
	auto tickend = std::chrono::high_resolution_clock::now();
	if ((tickend - tick).count() / 10000000 > 1/6) {
		tick = std::chrono::high_resolution_clock::now();

		if (ray::IsKeyDown(ray::KEY_D)) player.move(ray::Vector2(1, 0));
		if (ray::IsKeyDown(ray::KEY_S)) player.move(ray::Vector2(0, 1));
		if (ray::IsKeyDown(ray::KEY_A)) player.move(ray::Vector2(-1, 0));
		if (ray::IsKeyDown(ray::KEY_W)) player.move(ray::Vector2(0, -1));

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
	}

	return false;
}