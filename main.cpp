#include "game.h"
#include "data.h"
#include "classes.h"
#include "window.h"

void main() {

	window.Init();

	int run = 1;

	while (run) {
		if (ray::WindowShouldClose()) run = 0;

		if (ray::IsKeyDown(ray::KEY_D)) player.move(ray::Vector2(1,  0));
		if (ray::IsKeyDown(ray::KEY_S)) player.move(ray::Vector2(0,  1));
		if (ray::IsKeyDown(ray::KEY_A)) player.move(ray::Vector2(-1, 0));
		if (ray::IsKeyDown(ray::KEY_W)) player.move(ray::Vector2(0, -1));

		//if (ray::IsKeyDown(ray::KEY_SPACE)) player;

		player.draw();

		ray::BeginDrawing();
		ray::EndDrawing();
		ray::ClearBackground(SKYBLUE);
	}

	ray::CloseWindow();

	return;
}

