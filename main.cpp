#include <iostream>
#include <raylib.h>
#include <stvlib.h>
#include "game.h"

Player player(ray::Vector2(125,125));

int main()
{
	window.Init();

	int run = 1;

	while (run) {
		if (ray::WindowShouldClose()) run = 0;

		player.draw();

		ray::BeginDrawing();
		ray::EndDrawing();
		ray::ClearBackground(SKYBLUE);
	}

	ray::CloseWindow();
}

