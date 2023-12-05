#include "game.h"
#include "data.h"
#include "classes.h"
#include "window.h"
#include "menu.h"

void main() {

	window.Init();

	int run = 1;
	gameRunning = 0;
	player.health = 10;

	int x = window_size.x;
	for (int i = 0; i < 10; i++) asteroids.push_back(Asteroid(ray::Vector2(rand() % x, 0), ray::Vector2(75, 75), 1, 10));

	while (run) {
		if (ray::WindowShouldClose()) run = 0;

		if (ray::IsKeyDown(ray::KEY_D)) player.move(ray::Vector2(1,  0));
		if (ray::IsKeyDown(ray::KEY_S)) player.move(ray::Vector2(0,  1));
		if (ray::IsKeyDown(ray::KEY_A)) player.move(ray::Vector2(-1, 0));
		if (ray::IsKeyDown(ray::KEY_W)) player.move(ray::Vector2(0, -1));

		//if (ray::IsKeyDown(ray::KEY_SPACE)) player;

		if (gameRunning) {
			gameplay(1);

			player.draw();
			for (int i = 0; i < asteroids.size() - 1; i++) {
				asteroids[i].update(1);
				if (!gameRunning) {
					break;
				}
				asteroids[i].draw();
			}
		}
		else {
			menu();
		}

		ray::BeginDrawing();
		ray::EndDrawing();
		ray::ClearBackground(SKYBLUE);
	}

	ray::CloseWindow();

	return;
}

