#include "game.h"
#include "data.h"
#include "classes.h"
#include "window.h"
#include "menu.h"

#include <thread>

void main() {

	window.Init();

	int run = 1;
	gameRunning = 0;

	bullet = ray::LoadTexture("assests/256px/Minigun_Medium_png_processed.png");
	asteroid = ray::LoadTexture("assests/256px/Asteroid 01_png_processed.png");
	spaceship1 = ray::LoadTexture("assests/256px/PlayerRed_Frame_01_png_processed.png");
	ray::Texture background = ray::LoadTexture("assests/PixelBackgroundSeamlessVertically.png");
	background.width = window_size.x;
	background.height = window_size.y;
	bullet.height = 30;
	bullet.width = 20;

	auto start = std::chrono::high_resolution_clock::now();

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

		if (gameRunning) {


			auto end = std::chrono::high_resolution_clock::now();

			if ((end - start).count() / 10000000 > 15) {
				start = std::chrono::high_resolution_clock::now();
				if (ray::IsKeyDown(ray::KEY_SPACE)) bullets.emplace_back(Bullet(ray::Vector2(player.position.x + player.size.x / 2 - 1, player.position.y), btype, damage));
			}

			if (score > highscore) highscore = score;

			player.draw();
			for (int i = 0; i < asteroids.size() - 1; i++) {
				asteroids[i].update();
				if (!gameRunning) {
					break;
				}
				asteroids[i].draw();
			}
			for (int i = 0; i < bullets.size(); i++) {
				bullets[i].update(i);
				bullets[i].draw();
			}
			for (int i : deadBullets) {
				bullets.erase(bullets.begin() + i, bullets.begin() + i + 1);
			}
			deadBullets = {};

		}
		else {
			menu();
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

