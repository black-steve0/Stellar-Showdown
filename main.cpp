#include "game.h"
#include "data.h"
#include "classes.h"
#include "window.h"
#include "menu.h"
#include "textures.h"

void main() {

	window.Init();

	int run = 1;
	gameRunning = 0;

	font = ray::LoadFont("resources/fonts/romulus.png");

	loadTetures();

	auto start = std::chrono::high_resolution_clock::now();
	auto pstart = std::chrono::high_resolution_clock::now();

	while (run) {
		if (ray::WindowShouldClose()) run = 0;

		if (ray::IsKeyDown(ray::KEY_D)) player.move(ray::Vector2(1,  0));
		if (ray::IsKeyDown(ray::KEY_S)) player.move(ray::Vector2(0,  1));
		if (ray::IsKeyDown(ray::KEY_A)) player.move(ray::Vector2(-1, 0));
		if (ray::IsKeyDown(ray::KEY_W)) player.move(ray::Vector2(0, -1));


		if (ray::IsKeyDown(ray::KEY_ONE)) btype = 1;
		if (ray::IsKeyDown(ray::KEY_TWO)) btype = 2;
		if (ray::IsKeyDown(ray::KEY_THREE)) btype = 3;
		if (ray::IsKeyDown(ray::KEY_FOUR)) btype = 4;

		ray::DrawTexture(background, 0, 0, WHITE);

		if (page == 1) {
			auto end = std::chrono::high_resolution_clock::now();
			auto pend = std::chrono::high_resolution_clock::now();

			if ((end - start).count() / 10000000 > 10) {
				start = std::chrono::high_resolution_clock::now();
				if (ray::IsKeyDown(ray::KEY_SPACE)) bullets.emplace_back(Bullet(BulletIdCount++, ray::Vector2(player.position.x + player.size.x / 2 - 1, player.position.y), btype, damage));
			}
			if ((pend - pstart).count() / 10000000 > 6000) {
				pstart = std::chrono::high_resolution_clock::now();
				powerUPs.emplace_back(PowerUP(PowerUPIdCount++, rand() % 4, (rand() % 50 + 150)/100));
			}

			if (score > highscore) highscore = score;

			player.draw();
			for (int i = 0; i < asteroids.size() - 1; i++) {
				if (asteroids.size()) {
					asteroids[i].draw();
					asteroids[i].update();
				}
				else {
					break;
				}
			}
			for (Bullet& bul : bullets) {
				bul.update();
				bul.draw();
			}
			for (PowerUP& powerup : powerUPs) {
				powerup.update();
				powerup.draw();
			}

			ray::DrawTexture(menuUI, 0, 230, WHITE);
			ray::DrawText((std::to_string(score)).c_str(), 50, window_size.y - 30 - 50 / 2, 50, GOLD);

			std::cout << player.health << std::endl;
		}
		else if (page == 0) {
			menu();
		}
		else if (page == 1) {
			shop();
		}

		ray::DrawFPS(0,0);

		ray::BeginDrawing();
		ray::EndDrawing();
		ray::ClearBackground(SKYBLUE);
	}

	ray::UnloadTexture(spaceship1);

	ray::CloseWindow();

	return;
}

